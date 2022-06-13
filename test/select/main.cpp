#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <sys/select.h>

using namespace std;

int efd;
bool isExit;
void* func1 (void* param){
	fd_set reads, writes, tmp1, tmp2;
	FD_ZERO(&reads);
	FD_ZERO(&writes);
	
	FD_SET(efd, &reads);
	
	timeval ttime;
	while(!isExit){
		static long long i=0;
		tmp1 = reads;
		tmp2 = writes;
		ttime.tv_usec = 0;
		ttime.tv_sec = 3;
		select(efd+1, &tmp1, NULL, NULL, &ttime);
		cout << "time(null) = " << time(NULL) << endl;	
	//	sleep(1);
	}

	return nullptr;
}
int main(){
	isExit = false;
	efd = eventfd(0, 0);
	pthread_t thread_id;	
	int ret =  pthread_create(&thread_id, NULL, func1, NULL);
	if(ret != 0){
		cout << "thread create is error" << endl;
		return 0;
	}

	sleep(26);
	cout << "start pthread_join" << endl;
	eventfd_write(efd,10);
	isExit = true;
	pthread_join(thread_id, nullptr);
	return 0;


}

