#ifndef __Singleton_H__
#define __Singleton_H__


#define	SingletonClase(ClassType);	public: static ClassType* getInstance() { static ClassType instance; return &instance; }

/*
//Ê¾Àý
*/
class Singleton
{
	SingletonClase(Singleton);
};

#endif