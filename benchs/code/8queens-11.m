meld fil       y                                               "       "                     -       -                     !       !       8       8                     ,       ,       C       C       7       7       N       N       B       B       Y       Y       M       M       d       d       X       X       o       o       c       c       n       n                     #       #       .       .                     9       9                     D       D       O       O       Z       Z       e       e       p       p                     $       $       /       /                     :       :                     E       E       P       P       [       [       f       f       q       q                     %       %       0       0                     ;       ;                     F       F       Q       Q       \       \       g       g       r       r                     &       &       1       1                     <       <                     G       G       R       R       ]       ]       h       h       s       s                     '       '       2       2                     =       =                     H       H       S       S       ^       ^       i       i       t       t                     (       (       3       3                     >       >                     I       I       T       T       _       _       j       j       u       u                     )       )       4       4                     ?       ?                     J       J       U       U       `       `       k       k       v       v                     *       *       5       5       	       	       @       @                     K       K       V       V       a       a       l       l       w       w                       +       +       6       6       
       
       A       A                     L       L       W       W       b       b       m       m       x       x        	                init -o axioms�   propagate-left(Nodes, Coords) -o test-and-send-down(Nodes, Coords), {L | !left(L), 
			L != host-id | propagate-left(Nodes, Coords)@L}.�   propagate-right(Nodes, Coords) -o test-and-send-down(Nodes, Coords), {R | !right(R), 
			R != host-id | propagate-right(Nodes, Coords)@R}.T   test-and-send-down(Nodes, Coords), !coord(X, Y) -o test-y(Y, Coords, Nodes, Coords).x   test-y(Y, MV48, Nodes, Coords), !coord(OX, OY), test-nil(MV48) -o test-diag-left(OX - 1, OY - 1, Coords, Nodes, Coords).�   test-y(MV69, MV70, MV71, MV72), MV74 = head(MV73), MV73 = tail(MV70), not(test-nil(MV70)), 
			not(test-nil(MV73)) -o (MV69 = MV74 -o 1), OR (RestCoords = tail(MV73), MV69 != MV74 -o test-y(MV69, RestCoords, MV71, MV72)).�   test-diag-left(X, Y, MV46, Nodes, Coords), !coord(OX, OY), (X < 0) || (Y < 0) -o test-diag-right(OX - 1, OY + 1, Coords, Nodes, Coords).5  test-diag-left(MV75, MV76, MV77, MV78, MV79), MV82 = head(MV81), MV81 = tail(MV77), MV80 = head(MV77), 
			not(test-nil(MV77)), not(test-nil(MV81)) -o (MV75 = MV80, MV76 = MV82 -o 1), OR (RestCoords = tail(MV81), (MV75 != MV80) || (MV76 != MV82) -o test-diag-left(MV75 - 1, MV76 - 1, RestCoords, MV78, MV79)).�   test-diag-right(X, Y, MV61, Nodes, Coords), !coord(OX, OY), (X < 0) || (Y >= 11), test-nil(MV61) -o 
			send-down(cons(host-id,Nodes), cons(OX,cons(OY,Coords))).7  test-diag-right(MV83, MV84, MV85, MV86, MV87), MV90 = head(MV89), MV89 = tail(MV85), MV88 = head(MV85), 
			not(test-nil(MV85)), not(test-nil(MV89)) -o (MV83 = MV88, MV84 = MV90 -o 1), OR (RestCoords = tail(MV89), (MV83 != MV88) || (MV84 != MV90) -o test-diag-right(MV83 - 1, MV84 + 1, RestCoords, MV86, MV87)).V   send-down(Nodes, Coords), !coord(MV68, MV47), MV68 = 10 -o final-state(Nodes, Coords).�   send-down(Nodes, Coords) -o {B | !down-right(B), B != host-id | 
			propagate-right(Nodes, Coords)@B}, {B | !down-left(B), B != host-id | 
			propagate-left(Nodes, Coords)@B}.           �                  _init                                                               set-priority                                                        setcolor                                                            setedgelabel                                                        write-string                                                        add-priority                                                         schedule-next                                                       setColor2                                                            left                                                                 right                                                                down-right                                                           down-left                                                            coord                                                                propagate-left                                                       propagate-right                                                      test-and-send-down                                                    test-y                                                                test-diag-left                                                        test-diag-right                                                      send-down                                                            final-state                                                              �                                                                                                           !                      � 
�  y      i  �  #  �	  �  :  �  �  Q  �  C   �  �  Z  �	    q  �  +  �  �  z   �  4  �  �	  K  �    b  �    �     k  �  %
  �  �  <  �  �  S  �   E  �  �  \
  �    s  �  -  �    |  �  6  �
  �  M  �    d  �  V  �    m  �
  '  �  �  >  �  �  �  �  G  �    ^  �    u  �  /  �  !  ~  �  8  �  �  O  �  	  f  �  X  �  	  o  �  )  �  �  @  �  2  �  �  I	  �    `  �    w  �  @ p  p w 2   	                       
               �  2   	                      
"              �  2   	!                     
-              _  2   	,                     
8              (  2   	7       !              
C              �  2   	B       ,       "       
N              �  2   	M       7       -       
Y              �  2   	X       B       8       
d              L  2   	c       M       C       
o                2   	n       X       N       
c           	   �  2   	n       c       Y       
n           
   �  2   	                     
              p  2   	                     
#             9  2   	"                     
.               2   	-                     
9             �  2   	8       "              
D             �  2   	C       -       #       
O             ]  2   	N       8       .       
Z             &  2   	Y       C       9       
e             �  2   	d       N       D       
p             �  2   	o       Y       O       
d          	   �  2   	o       d       Z       
o          
   J  2   	                     
                2   	                     
$             �  2   	#                     
/             �  2   	.                     
:             n  2   	9       #              
E             7  2   	D       .       $       
P                2   	O       9       /       
[             �  2   	Z       D       :       
f             �  2   	e       O       E       
q             [  2   	p       Z       P       
e          	   $  2   	p       e       [       
p          
   �  2   	                     
              �  2   	                     
%               2   	$                     
0             H  2   	/                     
;               2   	:       $              
F             �  2   	E       /       %       
Q             �  2   	P       :       0       
\             l  2   	[       E       ;       
g             5  2   	f       P       F       
r             �  2   	q       [       Q       
f          	   �  2   	q       f       \       
q          
   �  2   	                     
              Y  2   	                     
&             "  2   	%                     
1             �  2   	0                     
<             �  2   	;       %              
G             }  2   	F       0       &       
R             F  2   	Q       ;       1       
]               2   	\       F       <       
h             �  2   	g       Q       G       
s             �  2   	r       \       R       
g          	   j  2   	r       g       ]       
r          
   3  2   	                     
              �  2   	                     
'             �  2   	&                     
2             �  2   	1                     
=             W  2   	<       &              
H                2   	G       1       '       
S             �  2   	R       <       2       
^             �  2   	]       G       =       
i             {  2   	h       R       H       
t             D  2   	s       ]       S       
h          	     2   	s       h       ^       
s          
   �  2   	                     
              �  2   	                     
(             h  2   	'                     
3             1  2   	2                     
>             �
  2   	=       '              
I             �
  2   	H       2       (       
T             �
  2   	S       =       3       
_             U
  2   	^       H       >       
j             
  2   	i       S       I       
u             �	  2   	t       ^       T       
i          	   �	  2   	t       i       _       
t          
   y	  2   	                     
              B	  2   	                     
)             	  2   	(                     
4             �  2   	3                     
?             �  2   	>       (              
J             f  2   	I       3       )       
U             /  2   	T       >       4       
`             �  2   	_       I       ?       
k             �  2   	j       T       J       
v             �  2   	u       _       U       
j          	   S  2   	u       j       `       
u          
     2   	                     
              �  2   	                     
*             �  2   	)              	       
5             w  2   	4                     
@             @  2   	?       )              
K             	  2   	J       4       *       
V             �  2   	U       ?       5       
a             �  2   	`       J       @       
l             d  2   	k       U       K       
w             -  2   	v       `       V       
k          	   �  2   	v       k       a       
v          
   �  2   	       	       	       
        	       �  2   	       	              
+       	      Q  2   	*              
       
6       	        2   	5                     
A       	      �  2   	@       *               
L       	      �  2   	K       5       +       
W       	      u  2   	V       @       6       
b       	      >  2   	a       K       A       
m       	        2   	l       V       L       
x       	      �  2   	w       a       W       
l       	   	   �  2   	w       l       b       
w       	   
   b  2   	       
       
       

       
       +  2   	        
              
       
      �  2   	+                      
        
      �  2   	6               +       
+       
      �  2   	A       +       6       
6       
      O  2   	L       6       A       
A       
        2   	W       A       L       
L       
      �   2   	b       L       W       
W       
      �   2   	m       W       b       
b       
      s   2   	x       b       m       
m       
   	   <   2   	x       m       x       
x       
   
      #         � �  �  �  �  �  �  �  �  �  �  �  }  t  X  O  F  =  !        �  �  �  �  �  �  �  �  |  s  j  a  E  <  3  *      �  �  �  �  �  �  �  �  �  �  i  `  W  N  2  )       �  �  �  �  �  �  �  �  �  �  {  r  V  M  D  ;          �  �  �  �  �  �  �  �  z  q  h  _  C  :  1  (      �  �  �  �  �  �  �  �  �  �  g  ^  U  L  0  '      �  �  �  �  �  �  �  �  �  �  y  p  T  K  B  9          �  �  �  �  �  �  �  �  x  o  f  ]  A  8  /  &  
    �  �  �  �  �  �  �  �  �  �  e  \  S  J  .  %      �  �  �  �  �  �  �  �  �  �  w  n  R  I  @  7      	     �  �  �  �  �  �  �  �  v  m  d  [  ?  6  -  $    �  �  �  �  �  �  �  �  �  �    c  Z  Q  H  ,  #      �  �  �  �  �  �  �  �  �  ~  u  l  P  G  >  5        �  �  �  �  �  �  �  �  �  t  k  b  Y  =  4  +  "    �  �  �  �  �  �  �  �  �  �  }  a  X  O  F  *  !      �  �  �  �  �  �  �  �  �  |  s  j  N  E  <  3        �  �  �  �  �  �  �  �  �  r  i  `  W  ;  2  )       �
  �
  �
  �
  �
  �
  �
  �
  �
  �
  {
  _
  V
  M
  D
  (
  
  
  
  �	  �	  �	  �	  �	  �	  �	  �	  �	  z	  q	  h	  L	  C	  :	  1	  	  	  	  �  �  �  �  �  �  �  �  �  p  g  ^  U  9  0  '      �  �  �  �  �  �  �  �  �  �  y  ]  T  K  B  &        �  �  �  �  �  �  �  �  �  x  o  f  J  A  8  /    
    �  �  �  �  �  �  �  �  �  n  e  \  S  7  .  %       �  �  �  �  �  �  �  �  �  �  w  [  R  I  @  $      	  �  �  �  �  �  �  �  �    v  m  d  H  ?  6  -      �  �  �  �  �  �  �  �  �  �  l  c  Z  Q  5  ,  #         o                  i    @%   % wA              ;    " 78`   @%   % " �� �         o                  i    @%   % wA           	   ;    " 78`   @%   % " �� �         N                  H               2    @! % %  % w� �         o                  i              Q    @"    :& "   :&% % % w� �         P                  J   Z S"  ;`	   � �"  <`   Y' { �         �                  �    "      >"     >A`W              Q    @"    :& "   =&% % % w� �         �                  �   Z ST "  ;`   " ;`	   � �"  <" <A`4   Y"     :&  "    :& ' { �         v                  p   "      >"    ?A`8              2    @7a  c b w� �         �   	               �   Z ST "  ;`   " ;`	   � �"  <" <A`4   Y"     :&  "    =& ' { �         J   
               D               .    
   @%   % w� �         �                  �    A           
   ;    " 78`   @%   % " �A              ;    " 78`   @%   % " �� �         