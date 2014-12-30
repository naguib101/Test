/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainget.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiazzal <jpiazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 18:35:16 by jpiazzal          #+#    #+#             */
/*   Updated: 2014/11/14 19:15:06 by jpiazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int		get_next_line(int const fd, char **line);

int        main(int ac, char **av)
{
   int        fd1;
   /*int        fd2;
   int        fd3;*/
   char    *str;
   int        ret1 = 1;
   int        ret2 = 0;
   int        ret3 = 0;
   int        i;

   i = 1;
   if (ac < 2)
   {
       fd1 = 0;
       while ((ret1 = get_next_line(fd1, &str)) > 0)
           printf("line %d : %s\n", i, str);
   }
   else
   {
       fd1 = open(av[1], O_RDONLY);
       /*fd2 = open(av[2], O_RDONLY);
       fd3 = open(av[3], O_RDONLY);*/
       while (ret1 || ret2 || ret3)
       { 
           if ((ret1 = get_next_line(fd1, &str)) > 0)
               printf("line %d : %s\n", i, str);
           /*if ((ret2 = get_next_line(fd2, &str)) > 0)
               printf("file 2 line %d : %s\n", i, str);
           if ((ret3 = get_next_line(fd3, &str)) > 0)
               printf("file 3 line %d : %s\n", i, str);*/
           i++;
       }
   }
   if (ret1 == 0 && ret2 == 0 && ret3 == 0)
       printf("Lecture finie\n");
   else
       printf("Erreur dans le read\n");
   close(fd1);
   return (0);
}
