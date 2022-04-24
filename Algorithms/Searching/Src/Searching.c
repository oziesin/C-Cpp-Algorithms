#include "Searching.h"

/************************************************ LINEAR SEARCH ************************************************
 * @Brief This function Searchs uxLookUp inside of puxData array linearly.
 * DATA_TYPE is configurable data types such as unint8_t,unint16_t,etc.. 
 * @Param puxData is array.
 * @Param uxLen is size of array.
 * @Param uxLookUp is search element.
 * @Returns Function returns index of array,if uxLookUp exist inside of array otherwise returns 0xFF as an ERROR.
 ****************************************************************************************************************/
DATA_TYPE LinearSearch( DATA_TYPE* puxData, size_t uxLen ,DATA_TYPE uxLookUp )
{
    DATA_TYPE uxIdx;
    uxIdx = 0;
    for ( uxIdx = 0; uxIdx < uxLen; ++uxIdx)
    {
        if ( puxData[ uxIdx ] == uxLookUp )
        {
            return uxIdx;
        }

    }
    return SEARCH_FAULT;
}

/************************************************ BINARY SEARCH ************************************************
 * @Brief This function Searchs uxLookUp inside of puxData array breaking into pieces.
 * DATA_TYPE is configurable data types such as unint8_t,unint16_t,etc.. 
 * @Param puxData is array.
 * @Param uxLeft is element of array that leftest.
 * @Param uxRiht is element of array that rightest.
 * @Param uxLookUp is search element.
 * @Returns Function returns index of array,if uxLookUp exist inside of array otherwise returns 0xFF as an ERROR.
 ****************************************************************************************************************/
DATA_TYPE BinarySearch( DATA_TYPE* puxData, DATA_TYPE uxLeft, DATA_TYPE uxRight, DATA_TYPE uxLookUp )
{
    if (uxRight >= uxLeft )
    {
        DATA_TYPE uxMid = uxLeft + ( uxRight - 1 ) / 2;
        // If the element is present at the middle
        if ( puxData[ uxMid ] == uxLookUp )
        {
            return uxMid;
        }
        // If element is smaller than mid, then
        // it can only be present in left subarray
        else if ( puxData[ uxMid ] > uxLookUp )
        {
            return BinarySearch( puxData, uxLeft, (uxMid - 1) , uxLookUp );
        }
        // If element is greater than mid, then
        // it can only be present in right subarray
        else if ( puxData[ uxMid ] < uxLookUp )
        {
            return BinarySearch( puxData, (uxMid + 1), uxRight , uxLookUp );
        }

    }
    
    return SEARCH_FAULT;
}

/************************************************JUMP SEARCH ************************************************
 * @Brief This function Searchs uxLookUp inside of puxData by jump. Jumping coef is Sqrt(length of array).
 * DATA_TYPE is configurable data types such as unint8_t,unint16_t,etc.. 
 * @Param puxData is array.
 * @Param uxLen is size of array.
 * @Param uxLookUp is search element.
 * @Returns Function returns index of array,if uxLookUp exist inside of array otherwise returns 0xFF as an ERROR.
 ****************************************************************************************************************/

DATA_TYPE JumpSearch( DATA_TYPE* puxData, size_t uxLen ,DATA_TYPE uxLookUp )
{
    DATA_TYPE uxJump,uxIdx;

    uxJump = floor( sqrt( uxLen ) );

    for ( uxIdx = 0; uxIdx < uxLen; uxIdx+=uxJump )
    {
        while ( uxIdx >= 0 && puxData [uxIdx] >= uxLookUp )
        {
            if (puxData [ uxIdx ] == uxLookUp)
            {
                return uxIdx;
            }
            uxIdx--;
        }
    }
    return SEARCH_FAULT;
}

/************************************************STRING SEARCH ************************************************
 * @Brief This function Searchs pat string inside of text string.
 * @Param text is char array .
 * @Param pat is char array  which is searched inside of text.
 * @Returns Function returns false = 0, if pat is not a part of text.Otherwise returns true = 1;
 ****************************************************************************************************************/
e_Bool exactMatch(char *text, char *pat)
{
    if (*text == '\0' && *pat != '\0')
        return False;
  
    // Else If last character of pattern reaches
    if (*pat == '\0')
        return True;
  
    if (*text == *pat)
        return exactMatch(text + 1, pat + 1);
  
    return False;
}
e_Bool StringSearch(char *text, char *pat)
{
    // If last character of text reaches
    if (*text == '\0')
        return False;
  
    // If current characters of pat and text match
    if (*text == *pat)
        if(exactMatch(text, pat))
            return 1;
        else
          return StringSearch(text + 1, pat);
  
    // If current characters of pat and tex don't match
    return StringSearch(text + 1, pat);
}