PROGS = sish listtest sum_args_list

all : ${PROGS}

sish : sish.c
	gcc -o sish sish.c

listtest : listtest.c list.c list.h
	gcc -o listtest listtest.c list.c

sum_args_list : sum_args_list.c list.c list.h debug_panic.c
	gcc -o sum_args_list sum_args_list.c list.c debug_panic.c

clean :
	rm ${PROGS}

