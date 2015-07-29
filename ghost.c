/*  ghost.c - Demonstra a passagem de argumentos por linha de comando a um módulo do kernel linux.
		
	# compilando:
	$ make

	# Para mostrar que os módulos do kernel estão actualmente carregados
	$ lsmod | grep ghost

	# Instala modulo
	$ sudo insmod ghost.ko mystring="nvGhost!" mybyte=256 myintArray=1,-2

	# Remove modulo do kernel
	$ sudo rmmod ghost
	Adeus, Ghost retornando ao mundo dos codigos mortais.

	# Instala modulo
	$ sudo insmod ghost.ko mystring="Agora o kernel pertence ao nvGhost." mybyte=256 myintArray=1,-2

	# Para ver as mensagens enviadas pelo modulo em syslog
	$ dmesg | tail
	$ tail -f /var/log/syslog
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neviim Jads");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 7777;
static char *mystring = "Agora o kernel pertence ao nvGhost!";
static int myintArray[2] = { -1, -1 };
static int arr_argc = 0;

/* 
 * module_param(foo, int, 0000)
 * O primeiro parametro é o nome
 * O segundo parametro é o seu tipo de dado
 * O argumento final é os bits de permissões, 
 * Para expor parâmetro em sysfs (se não-zero), numa fase posterior.
 */
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "Um inteiro curto");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "Um numero inteiro");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "Um inteiro longo");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "Uma cadeia de caracteres");

/* 
* Module_param_array (nome, tipo, num, perm); 
* O primeiro parâmetro é (no caso da matriz) o nome do parâmetro 
* O segundo parâmetro é o tipo dos elementos da matriz de dados 
* O terceiro argumento é um ponteiro para a variável que vai armazenar o 
* número de elementos da matriz inicializado pelo usuário no módulo de tempo de carregamento 
* O quarto argumento é os bits de permissão 
*/
module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "Um array de inteiros");

static int __init comando_init(void)
{
	int i;
	printk(KERN_INFO ".");
	printk(KERN_INFO "Ola usuario mortal :)! \n===================================\n");
	printk(KERN_INFO "myshort..é um inteiro curto..: %hd\n", myshort);
	printk(KERN_INFO "myint....é um numero inteiro.: %d\n ", myint);
	printk(KERN_INFO "mylong...é um inteiro longo..: %ld\n", mylong);
	printk(KERN_INFO "mystring.é uma string........: %s\n ", mystring);
	printk(KERN_INFO ".");

	for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
	{
		printk(KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i]);
	}

	printk(KERN_INFO "obteve %d argumentos para myintArray.\n", arr_argc);
	return 0;
}

static void __exit comando_exit(void)
{
	printk(KERN_INFO ".");
	printk(KERN_INFO "Adeus, Ghost retornando ao mundo dos codigos mortais.\n");
	printk(KERN_INFO ".");
}

module_init(comando_init);
module_exit(comando_exit);
