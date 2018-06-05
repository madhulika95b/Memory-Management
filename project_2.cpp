#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#include<time.h>
int split_process[20];
int process_allocation[50];
typedef struct		// Memory block
{
    int is_free;
    int length;
}*MEM_B;

char *m_begin;
int mem_maxim;
int mem_alloc;
char *heap_last;

int mem_nw=0;
int mem_null=1;
int mem_use=2;
int avail=0;
int used=1;

void Memory_allocation(char *ptr, int length_in_bytes)
{
    /* store the ptr and length_in_bytes in global variable */
 
    
    mem_maxim = length_in_bytes;
    m_begin = ptr;
    mem_alloc = 0;
    heap_last = m_begin + length_in_bytes;
    
 
}
 
/* Case 2: To implement memory allocation in Dynamic partitioning */ 
void *my_malloc_dynamic(int elem_length)
{
    /* check whether any chunk (allocated before) is free first */
 
    MEM_B p_mcb;
    int flag = mem_null;
 
    p_mcb = (MEM_B)m_begin;
 
    while( heap_last > ( (char *)p_mcb + elem_length)   )
    {
 
        if ( p_mcb->is_free == 0)
        {
 
            if( p_mcb->length == 0)
            {
                flag = mem_nw;
                break;
            }
            if( p_mcb->length > (elem_length) )
            {
                flag = mem_use;
                break;
            }
        }
        p_mcb = (MEM_B) ( (char *)p_mcb + p_mcb->length);
 
 
    }
 
    if( flag != mem_null)
    {
        p_mcb->is_free = 1;
 
        if( flag == mem_nw)
        {
            p_mcb->length = elem_length;
        }
        mem_alloc += elem_length;
        return ( (char *) p_mcb );
    }
 
}
/* Case 2: To implement memory De-allocation in Dynamic partitioning */ 
void my_free_dynamic(void *p)
{
    /* Mark in MEM_B that this chunk is free */
    MEM_B ptr = (MEM_B)p;
    ptr--;
    ptr->is_free = avail;
    mem_alloc -= (ptr->length);
}
int value_final=0;
/* Case 3: To implement memory allocation in Static partitioning */ 
int my_malloc_static(int length)
{
	for(int j=0;j<20;j++)
	{
		if((split_process[j]-length)>0)
		{
			split_process[j]=split_process[j]-length;
			return j;
			value_final++;
			break;
		}
	}
}
/* Case 3: To implement memory De-allocation in Static partitioning */ 
void my_free_static(int process,int memory)
{
	int allocation=process_allocation[process];
	split_process[allocation]=split_process[allocation]+memory;
}
int main()
{
	char *predefined_memory;
	predefined_memory=(char *)malloc(102400);
        Memory_allocation(predefined_memory,102400);
        int total_process=50;
	int *total_memory[50];
        int finish=0;
        int counter=0;
        int complete=0;
        int complete1=0;
	int complete2=0;
        int counter1=0;
	int counter2=0;
	int process[total_process][2];
	
	for(int i=0;i<20;i++)
	{
		split_process[i]=5000;
	}
	
	struct timespec tps, tpe;
        double elapsedTime,elapsedTime1;
        srand(time(NULL));
        int a=10;
        for(int i=0;i<50;i++)
	{	
		for(int j=0;j<2;j++)
		{
			if(j==0)
			{
				process[i][j]=rand()%(2500-200)+200;
			}
			else
			{
				process[i][j]=rand()%(2048-10)+10;
			}
		}
	}
	/* Displays the process number, memory and cycles for the process */
	
	printf("Process_Number\tProcess Cycle\t Memory\n");
	for(int i=0;i<50;i++)
	{
		printf("%d\t\t",(i+1));
		for(int j=0;j<2;j++)
		{
			printf("%d",process[i][j]);
			printf("\t\t");
		}
		printf("\n");
	}
        int process_cycle[50];
        for(int m=0;m<50;m++)
	{
	  if(m==0)
	  {
		process_cycle[m]=process[m][0];
	  }
	  else
	  {
		process_cycle[m]=process[m][0]+ (50*m);
	  }
	}
	int value=0;
        int flag=0;
        char *p[50];
		
	/* Implementation of Case-1 using predefined malloc() and free() functions*/	
        clock_gettime(CLOCK_REALTIME, &tps);
	while(finish==0)
	{
		if(value==50)
		{
			flag=1;
			
		}
		if(complete==50)
		{
			finish=1;
			break;
		}
		if((counter%50==0)&&(flag==0))
		{
			printf("Process:%d\n",(value+1));
			p[value]=(char *)malloc(process[value][1]);
			value++;			
		}
		for(int k=0;k<50;k++)
		{
			if(counter==process_cycle[k])
			{
				printf("Free process:%d\n",(k+1));
				free(p[k]);
				complete++;
			}
		}
		counter++;		
	}
	clock_gettime(CLOCK_REALTIME, &tpe);
        printf("%.5f s\n",(double)(tpe.tv_nsec-tps.tv_nsec)/1000000000);
		
	int value1=0;
        int flag1=0;
        int finish1=0;
        char *p1[50];
        struct timespec tps1, tpe1;
		
	/* Impementation of Case-2 Dynamic Partitioning*/	
	clock_gettime(CLOCK_REALTIME, &tps1);
	while(finish1==0)
	{
		if(value1==50)
		{
			flag1=1;
			
		}
		if(complete1==50)
		{
			finish1=1;
			break;
		}
		if((counter1%50==0)&&(flag1==0))
		{
			printf("Process:%d\n",(value1+1));
			p1[value1]=(char*)my_malloc_dynamic(process[value1][1]);
			value1++;			
		}
		for(int k=0;k<50;k++)
		{
			if(counter1==process_cycle[k])
			{
				printf("Free process:%d\n",(k+1));
				my_free_dynamic(p1[k]);
				complete1++;
			}
		}
		counter1++;		
	}
	clock_gettime(CLOCK_REALTIME, &tpe1);
	printf("%.5f s\n",(double)(tpe1.tv_nsec-tps1.tv_nsec)/1000000000);
 	int value2=0;
        int flag2=0;
        int finish2=0;
        struct timespec tps2, tpe2;
	/* Impementation of Case-3 Static Partitioning*/	
	clock_gettime(CLOCK_REALTIME, &tps2);
	while(finish2==0)
	{
		if(value2==50)
		{
			flag2=1;
			
		}
		if(complete2==50)
		{
			finish2=1;
			break;
		}
		if((counter2%50==0)&&(flag2==0))
		{
			printf("Process:%d\n",(value2+1));
			process_allocation[value2]=my_malloc_static(process[value2][1]);
			//printf("%p\n",p2[value2]);
			value2++;			
		}
		for(int k=0;k<50;k++)
		{
			if(counter2==process_cycle[k])
			{
				printf("Free process:%d\n",(k+1));
				my_free_static(process_allocation[k],process[value2][1]);
				complete2++;
			}
		}
		counter2++;		
	}
	clock_gettime(CLOCK_REALTIME, &tpe2);
 	printf("%.5f s\n",(double)(tpe2.tv_nsec-tps2.tv_nsec)/1000000000);   	
        return 0;
}