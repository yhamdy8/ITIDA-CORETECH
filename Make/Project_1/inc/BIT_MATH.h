#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Var,BitNo)      ( Var|=(1<<BitNo) )

#define CLR_BIT(Var,BitNo)      ( Var&=~(1<<BitNo) )

#define TOG_BIT(Var,BitNo)   	( Var^=(1<<BitNo) )

#define GET_BIT(Var,BitNo)      ( Var>>(BitNo)&1   )

#define ASS_BIT(Var,BitNo,Val)	do{ if(Val==1) SET_BIT(Var,BitNo);	\
									else 	   CLR_BIT(Var,BitNo);}while(0)
	
#endif
