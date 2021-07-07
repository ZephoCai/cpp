#include<iostream>
#include<list>
using namespace std;

//观察者
//为那些在目标发生改变时需获得通知的对象定义一个更新接口。
class Observer {
public:
	virtual void update(int) = 0;
};

//目标
//目标知道它的观察者。可以有任意多个观察者观察同一个目标；
//提供注册和删除观察者对象的接口。
class Subject {
public:
	virtual void attach(Observer*) = 0;
	virtual void detach(Observer*) = 0;
	virtual void notify() = 0;
};

//具体观察者
//维护一个指向ConcreteSubject对象的引用；
//存储有关状态，这些状态应与目标的状态保持一致；
//实现Observer的更新接口以使自身状态与目标的状态保持一致
class ConcreteObserver : public Observer {
public:
	ConcreteObserver(Subject* pSubject) : m_pSubject(pSubject) {}

	void update(int val) {
		cout << "ConcreteObserver get the update. New State:" << val << endl;
	}
private:
	Subject* m_pSubject;
};

class ConcreteObserver2 : public Observer {
public:
	ConcreteObserver2(Subject* pSubject) : m_pSubject(pSubject) {}

	void update(int val) {
		cout << "ConcreteObserver2 get the update. New State:" << val << endl;
	}
private:
	Subject* m_pSubject;
};

//具体目标
//将有关状态存入各ConcreteObserver对象；
//当它的状态发生改变时，向它的各个观察者发出通知。
class ConcreteSubject : public Subject {
public:
	void attach(Observer* pObserver) {
		m_ObserverList.push_back(pObserver);
	}
	void detach(Observer* pObserver) {
		m_ObserverList.remove(pObserver);
	}
	void notify() {
		list<Observer*>::iterator it = m_ObserverList.begin();
		while (it != m_ObserverList.end()) {
			(*it)->update(m_iState);
			it++;
		}
	}
	void SetState(int state)
	{
		m_iState = state;
	}

private:
	list<Observer*> m_ObserverList;
	int m_iState;
};

int main()
{
	// Create Subject
	ConcreteSubject* pSubject = new ConcreteSubject();

	// Create Observer
	Observer* pObserver = new ConcreteObserver(pSubject);
	Observer* pObserver2 = new ConcreteObserver2(pSubject);

	// Change the state
	pSubject->SetState(2);

	// Register the observer
	pSubject->attach(pObserver);
	pSubject->attach(pObserver2);

	pSubject->notify();

	// Unregister the observer
	pSubject->detach(pObserver);

	pSubject->SetState(3);
	pSubject->notify();

	delete pObserver;
	delete pObserver2;
	delete pSubject;
}
