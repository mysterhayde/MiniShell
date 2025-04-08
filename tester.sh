#!/bin/sh

BLUE="\033[34m"
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

MYSHELL="./minishell"
BASH_SHELL="/bin/bash"

TMP_DIR="/tmp/myshell_test"
rm -rf "$TMP_DIR"
mkdir -p "$TMP_DIR"

COMMANDS_FILE="$TMP_DIR/commands.txt"
CMDS_MARKER_FILE="$TMP_DIR/commands_with_marker.txt"
MINISHELL_OUTPUT="$TMP_DIR/minishell_output.txt"
BASH_OUTPUT="$TMP_DIR/bash_output.txt"

SUPP_FILE="resources/a.supp"
VALGRIND_LOG="resources/tester_leaks.log"

# Traitement du flag Valgrind
VALGRIND_MODE=0
SHOW_VG_LOG=0
while [ "$#" -gt 0 ]; do
    case "$1" in
        -v|--valgrind)
            VALGRIND_MODE=1
            ;;
        --show-vg)
            SHOW_VG_LOG=1
            ;;
        *)
            echo "Usage: $0 [-v|--valgrind] [--show-vg]"
            exit 1
            ;;
    esac
    shift
done

# Écriture des commandes de test dans COMMANDS_FILE
cat > "$COMMANDS_FILE" <<'EOF'
echo Hello
echo Hello World
echo "hello"
echo "Hello World"
echo "Hello""World"
ls
ls -l
ls -la
/bin/ls
"/bin/ls"
"ls"
"ls -la"
echo "Hello World" > hello.txt
touch test.txt
echo Hello >test.txt World
EOF

# Création du fichier de commandes avec marqueur
rm -f "$CMDS_MARKER_FILE"
while IFS= read -r cmd; do
    [ -z "$cmd" ] && continue
    echo "$cmd" >> "$CMDS_MARKER_FILE"
    echo "echo __END__" >> "$CMDS_MARKER_FILE"
done < "$COMMANDS_FILE"

# Exécution de minishell avec toutes les commandes en une seule instance
if [ "$VALGRIND_MODE" -eq 1 ]; then
    printf "${BLUE}Exécution de minishell sous Valgrind (instance unique)...${RESET}\n"
    valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes \
        --suppressions="$SUPP_FILE" "$MYSHELL" < "$CMDS_MARKER_FILE" > "$MINISHELL_OUTPUT" 2> "$VALGRIND_LOG"
else
    printf "${BLUE}Exécution de minishell (instance unique, sans Valgrind)...${RESET}\n"
    "$MYSHELL" < "$CMDS_MARKER_FILE" > "$MINISHELL_OUTPUT" 2>&1
fi

# Exécution de bash avec les mêmes commandes
printf "${BLUE}Exécution de bash (instance unique)...${RESET}\n"
"$BASH_SHELL" < "$CMDS_MARKER_FILE" > "$BASH_OUTPUT" 2>&1

# (Optionnel) Filtrer la sortie de minishell pour supprimer le prompt personnalisé
sed '/MyShell/d' "$MINISHELL_OUTPUT" > "$TMP_DIR/minishell_output_filtered.txt"
mv "$TMP_DIR/minishell_output_filtered.txt" "$MINISHELL_OUTPUT"

# Découpage des sorties en tests individuels à l'aide du marqueur __END__
csplit -sz "$MINISHELL_OUTPUT" '/^__END__$/' '{*}' -f "$TMP_DIR/minishell_test_"
csplit -sz "$BASH_OUTPUT" '/^__END__$/' '{*}' -f "$TMP_DIR/bash_test_"

# Comptage du nombre de tests (basé sur le nombre de fichiers générés)
NUM_TESTS=$(ls "$TMP_DIR"/minishell_test_* 2>/dev/null | wc -l)
printf "${BLUE}Nombre de tests individuels détectés : %d${RESET}\n" "$NUM_TESTS"

# Comparaison individuelle des sorties
i=0
while [ $i -lt "$NUM_TESTS" ]; do
    idx=$(printf "%02d" "$i")
    MINI_TEST_FILE="$TMP_DIR/minishell_test_$idx"
    BASH_TEST_FILE="$TMP_DIR/bash_test_$idx"
    
    # Récupérer la commande testée depuis commands.txt (en ignorant les lignes vides)
    cmd_line=$(sed -n "$((i+1))p" "$COMMANDS_FILE")
    
    printf "${BLUE}Test %d : %s${RESET}\n" "$((i+1))" "$cmd_line"
    printf "${BLUE}Comparaison du test %d :${RESET}\n" "$((i+1))"
    if diff -u "$MINI_TEST_FILE" "$BASH_TEST_FILE" > /dev/null; then
        printf "  ${GREEN}-> Test %d réussi.${RESET}\n" "$((i+1))"
    else
        printf "  ${RED}-> Test %d échoué.${RESET}\n" "$((i+1))"
        printf "${RED}--- Différences : ---${RESET}\n"
        diff -u "$MINI_TEST_FILE" "$BASH_TEST_FILE"
    fi
    echo "------------------------"
    i=$((i+1))
done

if [ "$VALGRIND_MODE" -eq 1 ]; then
    if [ "$SHOW_VG_LOG" -eq 1 ]; then
        printf "${BLUE}Voici le contenu complet du rapport Valgrind :${RESET}\n"
        cat "$VALGRIND_LOG"
    fi
    printf "${BLUE}Le rapport complet de Valgrind est enregistré dans : %s${RESET}\n" "$VALGRIND_LOG"
fi

printf "${BLUE}Tous les tests sont terminés.${RESET}\n"
exit 0
