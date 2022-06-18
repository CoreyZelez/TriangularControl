#pragma once
class Test
{
private:
	int x;

public:
	Test(int x);


	int func(Test test)
	{
		return x > test.x;
	}
};

