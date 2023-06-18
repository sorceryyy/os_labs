#include "lib.h"
#include "types.h"

#define PHER_num 5

int dec = 0;
int hex = 0;
char str[6];
char cha = 0;
int ret = 0;

/*static unsigned long int next =1;*/
/*int rand(void) {*/
		/*next = next * 11036162 +12356;*/
		/*return (unsigned int)(next/65536)%32768;*/
/*}*/

void test_scanf() {
		// For lab4.1
		// Test 'scanf' 
		while(1){
				printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
				ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
				printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
				if (ret == 4)
						break;
		}

}

void test_semaphore() {
		// For lab4.2
		// Test 'Semaphore'
		int i = 4;

		sem_t sem;
		printf("Father Process: Semaphore Initializing.\n");
		ret = sem_init(&sem, 2);
		if (ret == -1) {
				printf("Father Process: Semaphore Initializing Failed.\n");
				exit();
		}

		ret = fork();
		if (ret == 0) {
				while( i != 0) {
						i --;
						printf("Child Process: Semaphore Waiting.\n");
						sem_wait(&sem);
						printf("Child Process: In Critical Area.\n");
				}
				printf("Child Process: Semaphore Destroying.\n");
				sem_destroy(&sem);
				exit();
		}
		else if (ret != -1) {
				while( i != 0) {
						i --;
						printf("Father Process: Sleeping.\n");
						sleep(128);
						printf("Father Process: Semaphore Posting.\n");
						sem_post(&sem);
				}
				printf("Father Process: Semaphore Destroying.\n");
				sem_destroy(&sem);
				exit();
		}


}

int create_new(int num) {
		int id = 0;
		sem_t starteat;
		sem_init(&starteat,0);

		for(int i = 1; i < num; i++ ) {
				/*printf("now i is:%d\n",i);*/
				int ret = fork();
				/*printf("after fork now i is:%d,ret:%d\n",i,ret);*/
				if (ret == 0) {
						id = i;
						/*printf("child id: %d\n",id);*/
						sem_wait(&starteat); //all child will blocked here
						break;
				}
				else {
						/*printf("father id: %d\n",id);*/
				} 
		}		

		if(id == 0) {
				printf("have generate all\n");
				for(int i = 1; i< num;i++) {
						sem_post(&starteat);
				}
		}

		return id;


}


void test_philosopher(){
		int id = 0;
		sem_t chopstick[PHER_num];
		//init sems
		for (int i = 0; i<PHER_num;i++){
				sem_init(chopstick + i,1);
		}

		id = create_new(5); //actually add father is 5 


		while(1)  {
				if(id % 2 == 0) {
						sem_wait(chopstick + (id % PHER_num));
						sleep(128);
						sem_wait(chopstick + ((id+1) % PHER_num));
						sleep(128);
						printf("philosopher %d : eat\n",id);
						sleep(128);
				}
				else {
						sem_wait(chopstick + ((id+1) % PHER_num));
						sleep(128);
						sem_wait(chopstick + (id % PHER_num));
						sleep(128);
						printf("philosopher %d : eat\n",id);
						sleep(128);
				}
				sem_post(chopstick + (id % PHER_num));
				sleep(128);
				sem_post(chopstick + ((id+1) % PHER_num));
				sleep(128);
				printf("philosopher %d : think\n",id);
				sleep(128);

		}
		return ;
}


void test_pro_con() {
		int max_item = 4; // the max of the item
		sem_t mutex = 1;
		sem_t full = 0;
		sem_t empty = max_item;
		sem_init(&mutex,mutex);
		sem_init(&full,full);
		sem_init(&empty,empty);

		int pro_con_num = 5;
		int id = create_new(pro_con_num);
		if(id % 5 != 0) {
				// now is producer
				while(1) {
						sem_wait(&empty);
						sleep(128);
						sem_wait(&mutex);
						sleep(128);
						printf("Producer %d: produce \n",id);
						sleep(128);
						sem_post(&mutex);
						sleep(128);
						sem_post(&full);
						sleep(128);
				}
		}
		else {
				//now is consumer
				while(1) {
						sem_wait(&full);
						sleep(128);
						sem_wait(&mutex);
						sleep(128);
						printf("Consumer : consume\n");
						sleep(128);
						sem_post(&mutex);
						sleep(128);
						sem_post(&empty);
						sleep(128);
				}
		}

}

void test_rea_wri() {
		int thread_num = 6;
		sem_t writemutex = 1;
		sem_t countmutex = 1;

		sem_init(&writemutex,writemutex);
		sem_init(&countmutex,countmutex);

		shared(4);
		int id = create_new(thread_num);
		if(id % 2 == 0) {
				//writer
				while(1) {
						sem_wait(&writemutex);
						sleep(128);
						printf("Writer %d: write\n",id);
						sleep(128);
						sem_post(&writemutex);
						sleep(128);

				}
		}
		else {
				//reader
				while(1) {
						sem_wait(&countmutex);
						sleep(128);
						if(shared(2) == 0) sem_wait(&writemutex);
						sleep(128);
						shared(1);
						sleep(128);
						sem_post(&countmutex);
						sleep(128);
						printf("Reader %d: read, total %d reader\n",id,shared(2));
						sleep(128);
						sem_wait(&countmutex);
						sleep(128);
						shared(0);
						sleep(128);
						if(shared(2) == 0) sem_post(&writemutex);
						sleep(128);
						sem_post(&countmutex);
						sleep(128);

				}
		}
}

int uEntry(void) {
		//test 4.1
		/*test_scanf();*/

		//test 4.2
		/*test_semaphore();*/


		// For lab4.3
		// TODO: You need to design and test the philosopher problem.
		/*test_philosopher();*/
		// Producer-Consumer problem and Reader& Writer Problem are optional.
		/*test_pro_con();*/
		test_rea_wri();

		return 0;
}
