int		ft_getnbr(char *s) { return (0); }
void	*ft_memset(void *b, int c, size_t len) { return (NULL); }
void	ft_bzero(void *s, size_t n) { (void)n; }
void	*ft_memcpy(void *s1, const void *s2, size_t n) { return (NULL); }
void	*ft_memccpy(void *s1, const void *s2, int c, size_t n) { return (NULL); }
void	*ft_memmove(void *s1, const void *s2, size_t n) { return (NULL); }
void	*ft_memchr(const void *s, int c, size_t n) { return (NULL); }
int		ft_memcmp(const void *s1, const void *s2, size_t n) { return (0); }
void	ft_putchar(char c) { (void)c; }
void	ft_putchar_fd(char c, int fd) { (void)c; }
void	ft_putstr(char const *s) { (void)s; }
void	ft_putstr_fd(char const *s, int fd) { (void)s; }
void	ft_putendl(char const *s) { (void)s; }
void	ft_putendl_fd(char const *s, int fd) { (void)s; }
char	*ft_strcat(char *s1, const char *s2) { return (NULL); }
size_t	ft_strlcat(char *dst, const char *src, size_t size) { return (0); }
char	*ft_strchr(const char *s, int c) { return (NULL); }
char	*ft_strrchr(const char *s, int c) { return (NULL); }
char	*ft_strstr(const char *s1, const char *s2) { return (NULL); }
char	*ft_strnstr(const char *s1, const char *s2, size_t n) { return (NULL); }
char	*ft_strncat(char *s1, const char *s2, size_t n) { return (NULL); }
size_t	ft_strlen(const char *str) { return (0); }
char	*ft_strcpy(char *s1, const char *s2) { return (NULL); }
char	*ft_strncpy(char *s1, const char *s2, size_t n) { return (NULL); }
void	ft_putnbr(int n) { (void)n; }
void	ft_putnbr_fd(int n, int fd) { (void)n; }
int		ft_atoi(const char *str) { return (0); }
char	*ft_itoa(int n) { return (NULL); }
int		ft_unspace(int c) { return (0); }
int		ft_isalnum(int c) { return (0); }
int		ft_isalpha(int c) { return (0); }
int		ft_isascii(int c) { return (0); }
int		ft_isdigit(int c) { return (0); }
int		ft_isprint(int c) { return (0); }
int		ft_tolower(int c) { return (0); }
int		ft_toupper(int c) { return (0); }
int		ft_strcmp(const char *s1, const char *s2) { return (0); }
int		ft_strncmp(const char *s1, const char *s2, size_t n) { return (0); }
char	*ft_strdup(const char *s1) { return (NULL); }
void	*ft_memalloc(size_t size) { return (NULL); }
void	ft_memdel(void **ap) { (void)ap; }
char	*ft_strnew(size_t size) { return (NULL); }
char	*ft_stradd(char *str) { return (NULL); }
void	ft_strdel(char **as) { (void)as; }
void	ft_strclr(char *s) { (void)s; }
int		ft_strequ(char const *s1, char const *s2) { return (0); }
int		ft_strnequ(char const *s1, char const *s2, size_t n) { return (0); }
void	ft_striter(char *s, void (*f)(char *)) { (void)s; }
void	ft_striteri(char *s, void (*f)(unsigned int, char *)) { (void)s; }
char	*ft_strmap(char const *s, char (*f)(char)) { return (NULL); }
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char)) { return (NULL); }
char	*ft_strsub(char const *s, unsigned int start, size_t len) { return (NULL); }
char	*ft_strjoin(char const *s1, char const *s2) { return (NULL); }
char	*ft_strtrim(char const *s) { return (NULL); }
char	**ft_strsplit(char const *s, char c) { return (NULL); }
int		ft_strisdigit(char *str) { return (0); }
t_list	*ft_lstnew(void const *content, size_t content_size) { return (NULL); }
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t)) { (void)alst; }
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t)) { (void)alst; }
void	ft_lstadd(t_list **alst, t_list *new) { (void)alst; }
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem)) { (void)lst; }
t_list	*ft_lstmap(t_list *lst, t_list * (*f)(t_list *elem)) { return (NULL); }
