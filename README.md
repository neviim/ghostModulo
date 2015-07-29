# Cria modulo basico para o kernel do linux


ghost.c - Demonstra a passagem de parametro por linha de comando a um módulo do kernel linux.
	
	# Baixar uma copia:
	$ git clone git@github.com:neviim/ghostModulo.git
	$ cd ghostModulo

	# compilando:
	$ make

	# Para mostrar que os módulos do kernel estão actualmente carregados:
	$ lsmod | grep ghost

	# Instala modulo:
	$ sudo insmod ghost.ko mystring="nvGhost!" mybyte=256 myintArray=1,-2

	# Remove modulo do kernel:
	$ sudo rmmod ghost
	Adeus, Ghost retornando ao mundo dos codigos mortais.

	# Instala modulo:
	$ sudo insmod ghost.ko mystring="Agora o kernel pertence ao nvGhost." mybyte=256 myintArray=1,-2

	# Para ver as mensagens enviadas pelo modulo em syslog tem duas formas:
	$ dmesg | tail
	$ tail -f /var/log/syslog
