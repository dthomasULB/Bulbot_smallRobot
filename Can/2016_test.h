const tileStatusType initialMap[MAP_SIZE] =
{	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR,
 	UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR, UNPR
 	};