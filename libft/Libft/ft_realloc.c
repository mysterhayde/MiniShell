#include "libft.h"

/**
 * @brief realloc
 * @param void *ptr you want to realloc
 * @param size_t size of the new ptr
 */
void	*ft_realloc(char *ptr, size_t size)
{
	void	*array;

	array = (void *)malloc(size);
	if (!array)
		return (NULL);
	ft_strcpy(array, ptr);
	free(ptr);
	return (array);
}
