#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include "libft.h"

int					g_sig;
char				*cur_ft, *testing;
char				**flist;
char				*libflist[] = {
	"ft_atoi.c",
	"ft_bzero.c",
	"ft_isalnum.c",
	"ft_isalpha.c",
	"ft_isascii.c",
	"ft_isdigit.c",
	"ft_isprint.c",
	"ft_itoa.c",
	"ft_memalloc.c",
	"ft_memccpy.c",
	"ft_memchr.c",
	"ft_memcmp.c",
	"ft_memcpy.c",
	"ft_memdel.c",
	"ft_memmove.c",
	"ft_memset.c",
	"ft_putchar.c",
	"ft_putchar_fd.c",
	"ft_putendl.c",
	"ft_putendl_fd.c",
	"ft_putnbr.c",
	"ft_putnbr_fd.c",
	"ft_putstr.c",
	"ft_putstr_fd.c",
	"ft_strcat.c",
	"ft_strchr.c",
	"ft_strclr.c",
	"ft_strcmp.c",
	"ft_strcpy.c",
	"ft_strdel.c",
	"ft_strdup.c",
	"ft_strequ.c",
	"ft_striter.c",
	"ft_striteri.c",
	"ft_strjoin.c",
	"ft_strlcat.c",
	"ft_strlen.c",
	"ft_strmap.c",
	"ft_strmapi.c",
	"ft_strncat.c",
	"ft_strncmp.c",
	"ft_strncpy.c",
	"ft_strnequ.c",
	"ft_strnew.c",
	"ft_strnstr.c",
	"ft_strrchr.c",
	"ft_strsplit.c",
	"ft_strstr.c",
	"ft_strsub.c",
	"ft_strtrim.c",
	"ft_tolower.c",
	"ft_toupper.c",
	"\n---- BONUS ----\n",
	"ft_lstadd.c",
	"ft_lstdel.c",
	"ft_lstdelone.c",
	"ft_lstiter.c",
	"ft_lstmap.c",
	"ft_lstnew.c"
};

void				sig_handler(int signo)
{
	if (signo == SIGSEGV)
		exit (printf("\r[ \033[91mSEGV\033[0m ] %s -> Testing: \033[93m'\033[96m%s\033[93m' \033[0m\nSuch segfault...\n", cur_ft, testing));
}

void				putct(char **t)
{
	int				i;

	for (i=0; t[i]; i++)
		printf("%s\n", t[i]);
}

void				strrev(char *s)
{
	int				i, j;

	for (i=0, j=strlen(s) - 1; i < j; i++, j--)
	{
		s[i] ^= s[j];
		s[j] ^= s[i];
		s[i] ^= s[j];
	}
}

void				*hb_memalloc(size_t size)
{
	unsigned char	*memory;
	size_t			i;

	if (!(memory = (unsigned char*)malloc(size)) || size < 0)
		return (NULL);
	i = 0;
	while (i < size)
		memory[i++] = 0;
	return (memory);
}

int					hb_unspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char				*hb_strnew(size_t size)
{
	char			*str;
	size_t			index;

	if (size == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	index = 0;
	while (index <= size)
		str[index++] = '\0';
	return (str);
}

char				*hb_strsub(char const *s, unsigned int start, size_t len)
{
	char			*ns;
	size_t			i;

	ns = hb_strnew(len + 1);
	i = 0;
	if (!ns || !s)
		return (NULL);
	for (i=0; len; i++, len--)
		ns[i] = s[start + i];
	ns[i] = '\0';
	return (ns);
}

char				*hb_strtrim(char const *s)
{
	char			*ns;
	size_t			start;
	size_t			len;

	start = 0;
	while (hb_unspace(s[start]))
		start++;
	len = strlen(s) - 1;
	while (hb_unspace(s[len]))
		len--;
	len = len + 1 - start;
	ns = (char *)malloc(len * sizeof(s));
	if (!ns)
		return (NULL);
	ns = hb_strsub(s, start, len);
	return (ns);
}

static size_t		hb_itoa_count_digits(int n)
{
	size_t		len;

	for (len=1; n >= 10; ++len)
		n /= 10;
	return (len);
}

static void			hb_itoa_rec_add_number(char *s, int n)
{
	if (n >= 10)
		hb_itoa_rec_add_number(s - 1, n / 10);
	*s = '0' + n % 10;
}

char				*hb_itoa(int n)
{
	char			*s;
	size_t			len;
	int				is_negative;

	is_negative = n >= 0 ? 0 : 1;
	if (is_negative)
		n = -n;
	if (n != -2147483648)
	{
		len = is_negative
			? hb_itoa_count_digits(n) + 1 : hb_itoa_count_digits(n);
		s = hb_strnew(len);
		if (s)
		{
			if (is_negative)
				s[0] = '-';
			hb_itoa_rec_add_number(s + len - 1, n);
		}
	}
	else
		s = strdup("-2147483648");
	return (s);
}

size_t				hb_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			rslt;

	rslt = strlen(src);
	i = strlen(dst);
	if (i < size)
		rslt += i;
	else
		rslt += size;
	if ((int)(size - strlen(dst) - 1) > 0)
		strncat(dst, src, size - strlen(dst) -1);
	return (rslt);
}

char				*hb_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (0);
}

char				*hb_strrchr(const char *s, int c)
{
	int				i;

	i = strlen(s);
	while (s[i] != c && i != 0)
		i--;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (0);
}

char				*hb_strstr(const char *s1, const char *s2)
{
	size_t			i;
	size_t			j;
	size_t			n;

	i = 0;
	j = 0;
	n = strlen(s1);
	if (strlen(s2) == 0)
		return ((char *)(s1));
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[j])
			j++;
		else
			j = 0;
		if (!s2[j])
			return ((char *)&s1[i - (j - 1)]);
		i++;
	}
	return (NULL);
}

char				*hb_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			nt;
	char			*match;

	i = 0;
	n++;
	if (*s2 == '\0' || !s2)
		return ((char *) s1);
	while (s1[i] && n)
	{
		j = i;
		nt = n;
		match = (char *) s2;
		while ((s1[j] == *match || *match == '\0') && nt--)
		{
			if (*match == '\0')
				return ((char *) s1 + i);
			j++;
			match++;
		}
		n--;
		i++;
	}
	return (NULL);
}

int					hb_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 != NULL && s2 != NULL)
		while ((*s1 || *s2) && n)
		{
			if (*s1 != *s2)
				return (0);
			s1++;
			s2++;
			n--;
		}
	return (1);
}

int					hb_strequ(char const *s1, char const *s2)
{
	if (s1 != NULL && s2 != NULL)
		while (*s1 || *s2)
		{
			if (*s1 != *s2)
				return (0);
			s1++;
			s2++;
		}
	return (1);
}

char				*hb_strjoin(char const *s1, char const *s2)
{
	char			*freshcat;

	if (!s1 || !s2)
		return (NULL);
	freshcat = hb_strnew(strlen(s1) + strlen(s2));
	if (!freshcat)
		return (freshcat);
	freshcat = strcat(freshcat, s1);
	freshcat = strcat(freshcat, s2);
	return (freshcat);
}

int					hb_ctablen(char **t)
{
	int				i;

	for (i=0; t[i]; i++);
	return (i);
}

static int			hb_countchar(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int			hb_countword(char const *s, char c)
{
	unsigned int	nb;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	nb = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		len = hb_countchar(s + i, c);
		if (len)
		{
			nb++;
			i += len;
		}
		else
			i++;
	}
	return (nb);
}

char				**hb_strsplit(char const *s, char c)
{
	char			**ret;
	unsigned int	i;
	unsigned int	nbword;
	unsigned int	nbchr;

	i = 0;
	nbword = 0;
	ret = (char **)malloc(sizeof(char *) * (hb_countword(s, c) + 1));
	if (s == 0)
		return (0);
	while (s[i])
	{
		nbchr = hb_countchar(s + i, c);
		if (nbchr)
		{
			ret[nbword] = hb_strsub(s, i, nbchr);
			nbword++;
			i += nbchr;
		}
		else
			i++;
	}
	ret[nbword] = '\0';
	return (ret);
}

char				*hb_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ns;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = strlen(s);
	ns = (char *) malloc(i * sizeof(s));
	i = 0;
	if (ns)
	{
		while (s[i])
		{
			ns[i] = f(i, s[i]);
			i++;
		}
	}
	return (ns);
}

char				*hb_strmap(char const *s, char (*f)(char))
{
	char			*str;
	int				i;

	i = 0;
	if (s && f)
	{
		str = (char *)malloc(strlen(s) + 1);
		while (s[i] != '\0')
		{
			str[i] = (*f)(s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

void				hb_toupper(char *s)
{
	if (*s >= 'a' && *s <= 'z')
		*s += 'A' - 'a';
}

void				hb_itoupper(unsigned int i, char *s)
{
	if (*s >= 'a' && *s <= 'z')
		*s += 'A' - 'a';
}

void				hb_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		while (*s)
		{
			f(i, s);
			i++;
			s++;
		}
	}
}

void				hb_striter(char *s, void (*f)(char *))
{
	if (s && f)
	{
		while (*s)
		{
			f(s);
			s++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////              ////////////////////////////////
//////////////////////////////////   CHECKING   ////////////////////////////////
//////////////////////////////////              ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int					checkft(int ix)
{
	int				i, j;
	void			*ptr, *ptr1, *ptr2;
	char			*tmp, *tmp1, *tmp2;
	char			**t1, **t2;
	char			*stest[] = {
		"13445",
		"-13445",
		"-0",
		"",
		"  /0339:@AZ\n[`az{	",
		"  		",
		"333333"
	};
	int				itest[] = {
		54321,
		0,
		10,
		11010,
		98765,
		-54321,
		-0
	};
	int				sz = 6;

	testing = strdup("Nothing");
	switch (ix)
	{
		case 0: ///////////////////////////////////////////////////////////////// atoi
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				if (ft_atoi(stest[i]) != atoi(stest[i]))
					return (-1);
			}
			break;
		case 1: ///////////////////////////////////////////////////////////////// bzero
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = strdup(stest[i]);
				tmp2 = strdup(stest[i]);
				bzero(tmp1, 4);
				ft_bzero(tmp2, 4);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 2: ///////////////////////////////////////////////////////////////// isalnum
			for (i=0; i <= sz; i++)
				if (!isalnum(stest[4][i]) || !ft_isalnum(stest[4][i]))
					if (isalnum(stest[4][i]) != ft_isalnum(stest[4][i]))
						return (-1);
			break;
		case 3: ///////////////////////////////////////////////////////////////// isalpha
			for (i=0; i <= sz; i++)
				if (!isalpha(stest[4][i]) || !ft_isalpha(stest[4][i]))
					if (isalpha(stest[4][i]) != ft_isalpha(stest[4][i]))
						return (-1);
			break;
		case 4: ///////////////////////////////////////////////////////////////// isascii
			for (i=0; i <= sz; i++)
				if (!isascii(stest[4][i]) || !ft_isascii(stest[4][i]))
					if (isascii(stest[4][i]) != ft_isascii(stest[4][i]))
						return (-1);
			break;
		case 5: ///////////////////////////////////////////////////////////////// isdigit
			for (i=0; i <= sz; i++)
				if (!isdigit(stest[4][i]) || !ft_isdigit(stest[4][i]))
					if (isdigit(stest[4][i]) != ft_isdigit(stest[4][i]))
						return (-1);
			break;
		case 6: ///////////////////////////////////////////////////////////////// isprint
			for (i=0; i <= sz; i++)
				if (!isprint(stest[4][i]) || !ft_isprint(stest[4][i]))
					if (isprint(stest[4][i]) != ft_isprint(stest[4][i]))
						return (-1);
			break;
		case 7: ///////////////////////////////////////////////////////////////// itoa
			for (i=0; i <= sz; i++)
				if (strcmp(hb_itoa(itest[i]),ft_itoa(itest[i])))
					return (-1);
			break;
		case 8: ///////////////////////////////////////////////////////////////// memalloc
			for (i=0; i <= sz - 2; i++)
			{
				testing = strdup(hb_itoa(itest[i]));
				if (!(hb_memalloc(itest[i])) || !(ft_memalloc(itest[i])))
				{
					if (hb_memalloc(itest[i]) != ft_memalloc(itest[i]))
						return (-1);
				}
				else
					if (strcmp(hb_memalloc(itest[i]),ft_memalloc(itest[i])))
						return (-1);
			}
			break;
		case 9: ///////////////////////////////////////////////////////////////// memccpy
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = memccpy(tmp1, stest[i], '3', 5);
				tmp2 = ft_memccpy(tmp2, stest[i], '3', 5);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			break;
		case 10: //////////////////////////////////////////////////////////////// memchr
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = memchr(stest[i], '3', 5);
				tmp2 = ft_memchr(stest[i], '3', 5);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			break;
		case 11: //////////////////////////////////////////////////////////////// memcmp
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (memcmp(stest[i], stest[j], strlen(testing)) != ft_memcmp(stest[i], stest[j], strlen(testing)))
					return (-1);
			}
			break;
		case 12: //////////////////////////////////////////////////////////////// memcpy
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = memcpy(tmp1, stest[i], 5);
				tmp2 = ft_memcpy(tmp2, stest[i], 5);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 13: //////////////////////////////////////////////////////////////// memdel
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				ptr = strdup(stest[i]);
				ft_memdel(&ptr);
				if (ptr)
					return (-1);
			}
			break;
		case 14: //////////////////////////////////////////////////////////////// memmove
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = memcpy(tmp1, stest[i], 5);
				tmp2 = ft_memcpy(tmp2, stest[i], 5);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 15: //////////////////////////////////////////////////////////////// memset
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = strdup(stest[i]);
				tmp2 = strdup(stest[i]);
				tmp1 = memset(tmp1, '3', 5);
				tmp2 = ft_memset(tmp2, '3', 5);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			break;
		case 16:
			return (42);
			break;
		case 17:
			return (42);
			break;
		case 18:
			return (42);
			break;
		case 19:
			return (42);
			break;
		case 20:
			return (42);
			break;
		case 21:
			return (42);
			break;
		case 22:
			return (42);
			break;
		case 23:
			return (42);
			break;
		case 24: //////////////////////////////////////////////////////////////// strcat
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = strcat(tmp1, stest[i]);
				tmp2 = ft_strcat(tmp1, stest[i]);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 25: //////////////////////////////////////////////////////////////// strchr
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (!hb_strchr(stest[i], '3') || !ft_strchr(stest[i], '3'))
				{
					if (hb_strchr(stest[i], '3') != ft_strchr(stest[i], '3'))
						return (-1);
				}
				else
					if (strcmp(hb_strchr(stest[i], '3'), ft_strchr(stest[i], '3')))
						return (-1);
			}
			break;
		case 26: //////////////////////////////////////////////////////////////// strclr
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				tmp = strdup(stest[i]);
				ft_strclr(tmp);
				if (strlen(tmp))
					return (-1);
			}
			break;
		case 27: //////////////////////////////////////////////////////////////// strcmp
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (strcmp(stest[i], stest[j]) != ft_strcmp(stest[i], stest[j]))
					return (-1);
			}
			break;
		case 28: //////////////////////////////////////////////////////////////// strcpy
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = strcpy(tmp1, stest[i]);
				tmp2 = ft_strcpy(tmp2, stest[i]);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 29: //////////////////////////////////////////////////////////////// strdel
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp = strdup(stest[i]);
				ft_strdel(&tmp);
				if (tmp)
					return (-1);
			}
			break;
		case 30: //////////////////////////////////////////////////////////////// strdup
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				if (strcmp(strdup(stest[i]), ft_strdup(stest[i])))
					return (-1);
			}
			break;
		case 31: //////////////////////////////////////////////////////////////// strequ
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (hb_strequ(stest[i], stest[j]) != ft_strequ(stest[i], stest[j]))
					return (0);
			}
			break;
		case 32: //////////////////////////////////////////////////////////////// striter
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = strdup(stest[i]);
				hb_striter(tmp1, hb_toupper);
				tmp2 = strdup(stest[i]);
				ft_striter(tmp2, hb_toupper);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1,tmp2))
						return (-1);
			}
			break;
		case 33: //////////////////////////////////////////////////////////////// striteri
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = strdup(stest[i]);
				hb_striteri(tmp1, hb_itoupper);
				tmp2 = strdup(stest[i]);
				ft_striteri(tmp2, hb_itoupper);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1,tmp2))
						return (-1);
			}
			break;
		case 34: //////////////////////////////////////////////////////////////// strjoin
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = hb_strjoin(stest[i], "_swagcat");
				tmp2 = ft_strjoin(stest[i], "_swagcat");
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 35: //////////////////////////////////////////////////////////////// strlcat
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				if (hb_strlcat(tmp1, stest[i], 5) != ft_strlcat(tmp2, stest[i], 5))
					return (-1);
			}
			break;
		case 36: //////////////////////////////////////////////////////////////// strlen
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				if (strlen(testing) != ft_strlen(testing))
					return (-1);
			}
			break;
		case 37: //////////////////////////////////////////////////////////////// strmap
			for (i=0; i <= sz; i++)
			{
				ptr = toupper;
				testing = strdup(stest[i]);
				tmp = strdup(stest[i]);
				tmp1 = hb_strmap(tmp, ptr);
				tmp = strdup(stest[i]);
				tmp2 = ft_strmap(tmp, ptr);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1,tmp2))
						return (-1);
			}
			break;
		case 38: //////////////////////////////////////////////////////////////// strmapi
			for (i=0; i <= sz; i++)
			{
				ptr = toupper;
				testing = strdup(stest[i]);
				tmp = strdup(stest[i]);
				tmp1 = hb_strmapi(tmp, ptr);
				tmp = strdup(stest[i]);
				tmp2 = ft_strmapi(tmp, ptr);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1,tmp2))
						return (-1);
			}
			break;
		case 39: //////////////////////////////////////////////////////////////// strncat
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = strncat(tmp1, stest[i], 5);
				tmp2 = ft_strncat(tmp1, stest[i], 5);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 40: //////////////////////////////////////////////////////////////// strncmp
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (strncmp(stest[i], stest[j], strlen(testing)) != ft_strncmp(stest[i], stest[j], strlen(testing)))
					return (-1);
			}
			break;
		case 41: //////////////////////////////////////////////////////////////// strncpy
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = (char *)malloc(sizeof(char) * 32);
				tmp2 = (char *)malloc(sizeof(char) * 32);
				tmp1 = strncpy(tmp1, stest[i], 5);
				tmp2 = ft_strncpy(tmp2, stest[i], 5);
				if (strcmp(tmp1, tmp2))
					return (-1);
			}
			break;
		case 42: //////////////////////////////////////////////////////////////// strnequ
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (hb_strnequ(stest[i], stest[j], 5) != ft_strnequ(stest[i], stest[j], 5))
					return (0);
			}
			break;
		case 43: //////////////////////////////////////////////////////////////// strnew
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				if (!hb_strnew(strlen(stest[i])) || !ft_strnew(strlen(stest[i])))
				{
					if (hb_strnew(strlen(stest[i])) != ft_strnew(strlen(stest[i])))
						return (-1);
				}
				else
					if (strcmp(hb_strnew(strlen(stest[i])), ft_strnew(strlen(stest[i]))))
						return (-1);
			}
			break;
		case 44: //////////////////////////////////////////////////////////////// strnstr
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = hb_strnstr("398", stest[i], 2);
				tmp2 = ft_strnstr("398", stest[i], 2);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = hb_strnstr("398", stest[i], 3);
				tmp2 = ft_strnstr("398", stest[i], 3);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			break;
		case 45: //////////////////////////////////////////////////////////////// strrchr
			for (i=0, j=sz-1; j >= 0; i++, j--)
			{
				testing = strdup(stest[i]);
				if (!hb_strrchr(stest[i], '3') || !ft_strrchr(stest[i], '3'))
				{
					if (hb_strrchr(stest[i], '3') != ft_strrchr(stest[i], '3'))
						return (-1);
				}
				else
					if (strcmp(hb_strrchr(stest[i], '3'), ft_strrchr(stest[i], '3')))
						return (-1);
			}
			break;
		case 46: //////////////////////////////////////////////////////////////// strsplit
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				t1 = hb_strsplit(stest[i], '3');
				t2 = ft_strsplit(stest[i], '3');
				if (hb_ctablen(t1) != hb_ctablen(t2))
					return (-1);
			}
			break;
		case 47: //////////////////////////////////////////////////////////////// strstr
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = hb_strstr("39", stest[i]);
				tmp2 = ft_strstr("39", stest[i]);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp1 = hb_strstr("398", stest[i]);
				tmp2 = ft_strstr("398", stest[i]);
				if (!tmp1 || !tmp2)
				{
					if (tmp1 != tmp2)
						return (-1);
				}
				else
					if (strcmp(tmp1, tmp2))
						return (-1);
			}
			break;
		case 48: //////////////////////////////////////////////////////////////// strsub
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				if (strcmp(hb_strsub(stest[i], 2, 5), ft_strsub(stest[i], 2, 5)))
					return (-1);
			}
			break;
		case 49: //////////////////////////////////////////////////////////////// strtrim
			for (i=0; i <= sz; i++)
			{
				testing = strdup(stest[i]);
				tmp = strdup(testing);
				if (hb_strtrim(tmp))
					if (strcmp(hb_strtrim(tmp), ft_strtrim(tmp)))
						return (-1);
			}
			break;
		case 50: //////////////////////////////////////////////////////////////// tolower
			for (i=0; i <= sz; i++)
				if (tolower(stest[4][i]) != ft_tolower(stest[4][i]))
					return (-1);
			break;
		case 51: //////////////////////////////////////////////////////////////// toupper
			for (i=0; i <= sz; i++)
				if (toupper(stest[4][i]) != ft_toupper(stest[4][i]))
					return (-1);
			break;

			////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////// B O N U S //////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////

		case 53:
			return (42);
			break;
		case 54:
			return (42);
			break;
		case 55:
			return (42);
			break;
		case 56:
			return (42);
			break;
		case 57:
			return (42);
			break;
		case 58:
			return (42);
			break;

	}
	return (0);
}

int					checkfile(char *str)
{
	int				i;

	for (i=0; flist[i]; i++)
		if (!strcmp(flist[i], str))
			return (0);
	return (-1);
}

void				moulin()
{
	int				i;

	for (i=0; libflist[i]; i++)
	{
		if (i == 52)
			printf("\033[96m%s\033[0m\n", libflist[i++]);
		cur_ft = strdup(libflist[i]);
		printf("[ .. ] %s", cur_ft);
		if (!checkfile(libflist[i]))
		{
			g_sig = 0;
			signal(SIGSEGV, sig_handler);
			if (!checkft(i))
				printf("\r[\033[1;92m OK \033[0m] %s\n", cur_ft);
			else if (checkft(i) == -1)
				printf("\r[\033[1;91m KO \033[0m] %s\n", cur_ft);
			else if (checkft(i) == 42)
				printf("\r[\033[0;37m NA \033[0m] %s\n", cur_ft);
		}
		else
			printf("\r[\033[1;30mNONE\033[0m] %s\n", cur_ft);
	}
}

int					main(int ac, char **av)
{
	int				i = 0;
	DIR				*dirp;
	struct dirent	*d;
	char			*fname;

	if (ac != 2)
		return (printf("\033[91mUsage: \033[92mmoulibadger\033[0m <libft_dir>\n"));
	if (!(dirp = opendir(av[1])))
		return (printf("\033[91mUsage: \033[92mmoulibadger\033[0m <libft_dir>\n"));
	flist = (char **)malloc(sizeof(char *) * 64);
	while (d = readdir(dirp))
	{
		strrev(fname = strdup(d->d_name));
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..") && !strncmp(fname, "c.", 2))
			flist[i++] = strdup(d->d_name);
	}
	closedir(dirp);
	if (i == 0)
		return (printf("\033[91m%s\033[0m: No source file in this repository...\n", av[1]));
	printf("\033[96m---------------------------\n\033[0m");
	printf("\033[96m------- moulibadger -------\n\033[0m");
	printf("\033[96m---------------------------\n\n\033[0m");
	moulin();
	//putct(libflist);
	return (0);
}
