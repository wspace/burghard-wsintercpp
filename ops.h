class OpPush: public Op
{
	int value;

public:
	OpPush( string& s, int& length )
	{
		if( s.length() == 0 )
		{
			length = -1;
			value = 0;
			return;
		}

		int i = 0;

		int _sign = 1;
		int _value = 0;
		if( s[0] == 'a' )
		{
			_sign = +1;
			++ i;
		}
		else if( s[0] == 'b' )
		{
			_sign = -1;
			++ i;
		}
		else if( s[0] == 'c' )
		{
		}

		while( ( i < s.length() ) && ( s[i] != 'c' ) )
		{
			if( s[i] == 'a' )
			{
				_value = 2 * _value;
			}
			else if( s[i] == 'b' )
			{
				_value = 2 * _value + 1;
			}
			
			++ i;
		}

		++ i;
		value = _sign * _value;

		if( i <= s.length() )
		{
			length = i;
		}
		else
		{
			length = -1;
		}
	}

	static const char* getSignature()
	{
		return "aa";
	}

	virtual const char* getName( )
	{
		return "push";
	}

	virtual void getRunInfo( ostream& out )
	{
		out << getName() << " " << value;
	}

	virtual void run( class Vm& vm )
	{
		vm.stack.push_back( value );
	}
};


class OpPop: public Op
{
public:
	OpPop( string& s, int& length )
	{
	}

	static const char* getSignature()
	{
		return "acc";
	}

	virtual const char* getName( )
	{
		return "pop";
	}

	virtual void run( class Vm& vm )
	{
		vm.stack.pop_back();
	}
};

class OpLabel: public Op
{
public:
//protected:
	int label;
	virtual bool isLabel() { return true; };

public:
	OpLabel( string& s, int& length )
	{
		if( s.length() == 0 )
		{
			length = -1;
			label = 0;
			return;
		}

		int i = 0;

		int _value = 1;
		while( ( i < s.length() ) && ( s[i] != 'c' ) )
		{
			if( s[i] == 'a' )
			{
				_value = 2 * _value;
			}
			else if( s[i] == 'b' )
			{
				_value = 2 * _value + 1;
			}
			
			++ i;
		}

		++ i;
		label = _value;

		if( i <= s.length() )
		{
			length = i;
		}
		else
		{
			length = -1;
		}
	}

	virtual const char* getName( )
	{
		return "label";
	}

	static const char* getSignature()
	{
		return "caa";
	}

	virtual void getRunInfo( ostream& out )
	{
		out << getName() << " " << label;
	}

	virtual void run( class Vm& vm )
	{
	}
};

class OpDoub: public Op
{
public:
	OpDoub( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "doub";
	}

	static const char* getSignature()
	{
		return "aca";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() > 0 );
		vm.stack.push_back( vm.stack.back() );
	}
};

class OpSwap: public Op
{
public:
	OpSwap( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "swap";
	}

	static const char* getSignature()
	{
		return "acb";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		swap( vm.stack[ size - 2 ], vm.stack[ size - 1] );
	}
};

class OpAdd: public Op
{
public:
	OpAdd( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "add";
	}

	static const char* getSignature()
	{
		return "baaa";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ] + vm.stack[ size - 1];
		vm.stack.pop_back();
		vm.stack.back() = i;
	}
};

class OpSub: public Op
{
public:
	OpSub( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "sub";
	}

	static const char* getSignature()
	{
		return "baab";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ] - vm.stack[ size - 1];
		vm.stack.pop_back();
		vm.stack.back() = i;
	}
};

class OpMul: public Op
{
public:
	OpMul( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "mul";
	}

	static const char* getSignature()
	{
		return "baac";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ] * vm.stack[ size - 1];
		vm.stack.pop_back();
		vm.stack.back() = i;
	}
};

class OpDiv: public Op
{
public:
	OpDiv( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "div";
	}

	static const char* getSignature()
	{
		return "baba";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ] / vm.stack[ size - 1];
		vm.stack.pop_back();
		vm.stack.back() = i;
	}
};

class OpMod: public Op
{
public:
	OpMod( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "mod";
	}

	static const char* getSignature()
	{
		return "babb";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ] % vm.stack[ size - 1];
		vm.stack.pop_back();
		vm.stack.back() = i;
	}
};

class OpStore: public Op
{
public:
	OpStore( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "store";
	}

	static const char* getSignature()
	{
		return "bba";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 2 );
		int size = vm.stack.size();
		int i = vm.stack[ size - 2 ];
		int v = vm.stack[ size - 1];

		putInHeap( vm, i, v );

		vm.stack.pop_back();
		vm.stack.pop_back();
	}
};

class OpRetrive: public Op
{
public:
	OpRetrive( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "retrive";
	}

	static const char* getSignature()
	{
		return "bbb";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		assert( vm.stack.back() >= 0 );
		assert( vm.heap.size() >= vm.stack.back() );
		vm.stack.back() = vm.heap[ vm.stack.back() ];
	}
};


class OpCall: public OpLabel
{
public:
	OpCall( string& s, int& length )
		: OpLabel( s, length )
	{
	}

	virtual const char* getName( )
	{
		return "call";
	}

	virtual bool isLabel() { return false; };

	static const char* getSignature()
	{
		return "cab";
	}

	virtual void run( class Vm& vm )
	{
//		vm.stack.push_back( vm.ip );
		vm.stack.insert( vm.stack.begin(), vm.ip );

		assert( vm.labels.find( label ) != vm.labels.end() );
		vm.ip = vm.labels[label];
	}
};

class OpJump: public OpLabel
{
public:
	OpJump( string& s, int& length )
		: OpLabel( s, length )
	{
	}

	virtual const char* getName( )
	{
		return "jump";
	}

	virtual bool isLabel() { return false; };

	static const char* getSignature()
	{
		return "cac";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.labels.find( label ) != vm.labels.end() );
		vm.ip = vm.labels[label];
	}
};

class OpJumpZ: public OpLabel
{
public:
	OpJumpZ( string& s, int& length )
		: OpLabel( s, length )
	{
	}

	virtual const char* getName( )
	{
		return "jumpz";
	}

	virtual bool isLabel() { return false; };

	static const char* getSignature()
	{
		return "cba";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		if( vm.stack.back() == 0 )
		{
			assert( vm.labels.find( label ) != vm.labels.end() );
			vm.ip = vm.labels[label];
		}
		vm.stack.pop_back();
	}
};

class OpJumpN: public OpLabel
{
public:
	OpJumpN( string& s, int& length )
		: OpLabel( s, length )
	{
	}

	virtual const char* getName( )
	{
		return "jumpn";
	}

	virtual bool isLabel() { return false; };

	static const char* getSignature()
	{
		return "cbb";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		if( vm.stack.back() < 0 )
		{
			assert( vm.labels.find( label ) != vm.labels.end() );
			vm.ip = vm.labels[label];
		}
		vm.stack.pop_back();
	}
};

class OpRet: public Op
{
public:
	OpRet( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "ret";
	}

	static const char* getSignature()
	{
		return "cbc";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
//		vm.ip = vm.stack.back();
		vm.ip = vm.stack.front();
//		vm.stack.erase( vm.stack.front(), vm.stack.front() + 1 );
		vm.stack.erase( vm.stack.begin(), vm.stack.begin() + 1 );
		//vm.stack.pop_back();
	}
};

class OpExit: public Op
{
public:
	OpExit( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "exit";
	}

	static const char* getSignature()
	{
		return "ccc";
	}

	virtual void run( class Vm& vm )
	{
		vm.running = false;
	}
};

class OpOutC: public Op
{
public:
	OpOutC( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "outc";
	}

	static const char* getSignature()
	{
		return "bcaa";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		cout << (char) vm.stack.back();
		vm.stack.pop_back();
	}
};

class OpOutN: public Op
{
public:
	OpOutN( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "outn";
	}

	static const char* getSignature()
	{
		return "bcab";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		cout << vm.stack.back();
		vm.stack.pop_back();
	}
};

class OpInC: public Op
{
public:
	OpInC( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "inc";
	}

	static const char* getSignature()
	{
		return "bcba";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		char ch;
//		cin >> ch;
		cin.get( ch );
		putInHeap( vm, vm.stack.back(), ch ); 
		vm.stack.pop_back();
	}
};

class OpInN: public Op
{
public:
	OpInN( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "inn";
	}

	static const char* getSignature()
	{
		return "bcbb";
	}

	virtual void run( class Vm& vm )
	{
		assert( vm.stack.size() >= 1 );
		int v;
		cin >> v;
		putInHeap( vm, vm.stack.back(), v ); 
		vm.stack.pop_back();
	}
};

class OpDebugPrintStack: public Op
{
public:
	OpDebugPrintStack( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "debugprintstack";
	}

	static const char* getSignature()
	{
		return "ccaaa";
	}

	virtual void run( class Vm& vm )
	{
		cout << "Stack: [";
		for( int i = 0; i < vm.stack.size(); ++ i )
		{
			 if( i > 0 )
			 {
				 cout << ",";
			 }
			 cout << vm.stack[i];
		}
		cout << "]" << endl;
	}
};

class OpDebugPrintHeap: public Op
{
public:
	OpDebugPrintHeap( string& s, int& length )
	{
	}

	virtual const char* getName( )
	{
		return "debugprintheap";
	}

	static const char* getSignature()
	{
		return "ccaab";
	}

	virtual void run( class Vm& vm )
	{
		cout << "Heap: [";
		for( int i = 0; i < vm.heap.size(); ++ i )
		{
			 if( i > 0 )
			 {
				 cout << ",";
			 }
			 cout << vm.heap[i];
		}
		cout << "]" << endl;
	}
};

typedef OpTemplateClass< OpPush    > OpClassPush;
typedef OpTemplateClass< OpPop     > OpClassPop;
typedef OpTemplateClass< OpLabel   > OpClassLabel;
typedef OpTemplateClass< OpDoub    > OpClassDoub;
typedef OpTemplateClass< OpSwap    > OpClassSwap;
typedef OpTemplateClass< OpAdd     > OpClassAdd;
typedef OpTemplateClass< OpSub     > OpClassSub;
typedef OpTemplateClass< OpMul     > OpClassMul;
typedef OpTemplateClass< OpDiv     > OpClassDiv;
typedef OpTemplateClass< OpMod     > OpClassMod;
typedef OpTemplateClass< OpStore   > OpClassStore;
typedef OpTemplateClass< OpRetrive > OpClassRetrive;
typedef OpTemplateClass< OpCall    > OpClassCall;
typedef OpTemplateClass< OpJump    > OpClassJump;
typedef OpTemplateClass< OpJumpZ   > OpClassJumpZ;
typedef OpTemplateClass< OpJumpN   > OpClassJumpN;
typedef OpTemplateClass< OpRet     > OpClassRet;
typedef OpTemplateClass< OpExit    > OpClassExit;
typedef OpTemplateClass< OpOutC    > OpClassOutC;
typedef OpTemplateClass< OpOutN    > OpClassOutN;
typedef OpTemplateClass< OpInC     > OpClassInC;
typedef OpTemplateClass< OpInN     > OpClassInN;
typedef OpTemplateClass< OpDebugPrintStack > OpClassDebugPrintStack;
typedef OpTemplateClass< OpDebugPrintHeap  > OpClassDebugPrintHeap;

