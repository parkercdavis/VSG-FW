
//--------------------------------------------------------------------------
//
//
//

#ifndef COMMONMACROS_HPP
#define COMMONMACROS_HPP

#ifndef SET_BIT
    #define SET_BIT(reg, n) reg |= (1 << n);
#endif

#ifndef SET_BITS
    #define SET_BITS(reg, start, stop) for(int i = start; i <= stop; i++) SET_BIT(reg, i)
#endif

#ifndef CLEAR_BIT
    #define CLEAR_BIT(reg, n) reg &= (1 & ~(1 << n));
#endif

#ifndef GET_BIT
    #define GET_BIT(reg, n) ((reg & (1 << n)) >> n)
#endif

#ifndef CLEAR_BITS
    #define CLEAR_BITS(reg, start, end) for(int i = start; i <= end; i++) CLEAR_BIT(reg, i)
#endif


#ifndef GET_BITS
    
#endif


#endif