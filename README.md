# maTricks

A MTX_GaussElim-ben használt függvények amik még nincsenek megírva : MTX_Malloc, MTX_Copy, MTX_ChangeRow

Update: a MTX_Mallocot megírtam. Tesztelve nem lett eddig semmelyik függvény se, majd ha meglesznek a i/o függvények és lesz egy konzolos felhasználó/tesztelői interfész akkor tudjuk őket tesztelni.

Update: Ezentúl minden forrásfájl kezdődjön 
#include "datatypes.h"
#include "prototypes.h"
#include "includes.h"
-vel :) Ha a forrásfájlhoz valamilyen másik header kell includeolt az includes.h-ban, ha csinálsz egy függvényt akkor deklaráld a prototypes.h-ba, analóg módon datatypes.h.. 
