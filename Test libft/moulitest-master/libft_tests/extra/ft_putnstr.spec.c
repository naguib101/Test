int		out;
int		p[2];
char	buf[5];

out = dup(1);
pipe(p);
dup2(p[1], 1);
ft_putnstr("Bonjour", 4);
dup2(out, 1);
read(p[0], buf, 4);
buf[4] = 0;
close(p[0]);
close(p[1]);
close(out);
UT_ASSERT_EQ(strcmp(buf, "Bonj"), 0);