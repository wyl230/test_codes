https://www.bogotobogo.com/cplusplus/libraries.php

```bash
$ gcc -c a.c
$ gcc -c b.c
$ ar -r mylib.a a.o b.o # 建立一个名为mylib.a的静态库
$ gcc main.c mylib.a
$ ./a.out
calling who\_are\_you()
I am A
$
```
