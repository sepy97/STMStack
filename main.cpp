#include <iostream>
#include <thread>

#define MAX_THREAD_NUM 10

class STMStack {
public:
	STMStack() :head(NULL) {}
	void push(int d)
	{
		Node *pv = new Node;
		pv->d = 0;//d;
		__transaction_atomic
		{
			pv->d = d;
			pv->p = head;
			head = pv;
		}
	}
	int pop()
	{
		if (head == NULL) return NULL;
		/*if (isEmpty())
		{
   			return -1;
		}*/
		
		int temp = -1;
		Node *pv = NULL;
		
		__transaction_atomic
		{
			temp = head->d;
			pv = head;
			head = head->p;
		}
		if (pv != NULL)	delete pv;
		return temp;
	}
	//bool isEmpty();
	void display();

private:
	struct Node {
		int d;
		Node *p;
	};
	
	Node *head;
};

void testPush (STMStack* toTest, int data)
{
	toTest->push (data);
}

int main ()
{
	STMStack testStack;
	
	std::thread thr[MAX_THREAD_NUM];
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		thr[i] = std::thread (testPush, &testStack, i);
	}
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		thr[i].join ();
	}
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		printf ("%d\n", testStack.pop());
	}

	
}
