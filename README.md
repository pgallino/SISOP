# SISOP
https://fisop.github.io/website/

## Material de sistemas operativos 2c2023

Manual completo teórico: https://github.com/pgallino/SISOP/blob/main/SISOP.pdf (de mi autoría) 

Tres trabajos grupales (3 integrantes):

### ***Shell***
Se desarrolla la funcionalidad mínima que caracteriza a un intérprete de comandos shell similar a lo que realizan bash, zsh, fish.

enunciado completo: https://github.com/pgallino/SISOP/blob/main/TP_shell/tp_shell_enunciado.pdf

### ***Scheduler***
Se implementa el mecanismo de cambio de contexto para procesos y el scheduler (i.e. planificador) sobre un sistema operativo preexistente. 
El kernel a utilizado es una modificación de JOS, un exokernel educativo con licencia libre del grupo de Sistemas Operativos Distribuidos del MIT.

enunciado completo: https://github.com/pgallino/SISOP/blob/main/TP_scheduler/enunciado_sched.pdf

### ***Filesystem FUSE***
Se implementa nuestro propio sistema de archivos (o filesystem) para Linux. El sistema de archivos utiliza el mecanismo de FUSE (Filesystem in USErspace) provisto por el kernel, que permite definir en modo usuario la implementación de un filesystem. Gracias a ello, el mismo tiene la interfaz VFS y puede ser accedido con las syscalls y programas habituales (read, open, ls, etc).

enunciado completo: https://github.com/pgallino/SISOP/blob/main/TP_filesystem/TP3_%20Filesystem%20FUSE.pdf
