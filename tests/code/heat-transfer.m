meld fil       d           c              b              Y              a              X              O              `              W              N       	       E       
       _              V              M              D              ;              ^              U              L              C              :              1              ]              T              K              B              9              0              '              \              S              J              A               8       !       /       "       &       #              $       [       %       R       &       I       '       @       (       7       )       .       *       %       +              ,              -       Z       .       Q       /       H       0       ?       1       6       2       -       3       $       4              5              6       	       7       P       8       G       9       >       :       5       ;       ,       <       #       =              >              ?              @       F       A       =       B       4       C       +       D       "       E              F              G              H       <       I       3       J       *       K       !       L              M              N              O       2       P       )       Q               R              S              T              U       (       V              W              X              Y              Z              [              \              ]              ^              _              `              a       
       b              c               	                init -o axioms*   !edge(X1, X2) -o !___egde(host-id, X2)@X1.]   neighborchanged(B, V, O), delta(P1, P2), !___egde(B, W) -o delta(P1 + (V * W), P2 + (O * W)).J   -o (heatchanged(O, X), heat(V), !inbound(T), fabs(X) > 7.5 -o 
			heat(V), {B, W | !edge(B, W) | add-priority(fabs(X) / 7.5)@B, 
			neighborchanged(host-id, V / float(T), O / float(T))@B}), OR (heatchanged(O, X), heat(V), !inbound(T) -o heat(V), 
			{B, W | !edge(B, W) | neighborchanged(host-id, V / float(T), O / float(T))@B}).�   delta(Plus, Minus), heat(V), count(C), !inbound(X), 
			fabs((Plus - Minus)) > 0.1 -o heatchanged(V, Plus - Minus), heat((V + Plus) - Minus), count(C + 1), delta(0.0, 0.0).           �       A   .        O `   .      �?H 5 `   .      �H 5 2!              _init                                                               set-priority                                                        setcolor                                                             setedgelabel                                                         write-string                                                        add-priority                                                         schedule-next                                                       setcolor2                                                            stop-program                                                         inbound                                                              edge                                                                 coord                                                                 inner                                                               heat                                                                heatchanged                                                         neighborchanged                                                     delta                                                               count                                                                ___egde                                                                  �                                                    @( ! "                                                  �&                   �&   � 
i&  d   �$  :$  W!  �#  �   �  �#  �   "  �  >#  (   �  R  �  �"  �  X  �  �    �"  ^  �  �    �  C  B"  �  �  #  �  K  �  s
  �!  �  )  �  R  �  y  
  �  �!  /  �  Y  �  �    �	  >  �  �  _  �  �    �  D	  �  �    �  "  �  J  �  t  <  ;  �  P  �  z    �  i  �  �    �  �  �    �  E  @  �
  K  �  �   �  {  �   '  D      >   
b          ����?
a          ����?      @        	   �$  O   
`          ����?
_          ����?
c          ����?      @       	   >$  O   
]          ����?
\          ����?
b          ����?      @       	   �#  O   
Y          ����?
X          ����?
`          ����?      @       	   �#  O   
T          ����?
S          ����?
]          ����?      @       	   B#  O   
N          ����?
M          ����?
Y          ����?      @       	   �"  O   
G          ����?
F          ����?
T          ����?      @       	   �"  O   
?          ����?
>          ����?
N          ����?      @       	   F"  O   
6          ����?
5          ����?
G          ����?      @       	   �!  >   
,          ����?
?          ����?      @    	   	   �!  O   
_          ����?
^          ����?
c          ����?      @       	   [!  `   
\          ����?
[          ����?
a          ����?
b          ����?      @      	   �   `   
X          ����?
W          ����?
_          ����?
`          ����?      @      	   �   `   
S          ����?
R          ����?
\          ����?
]          ����?      @      	   ,   `   
M          ����?
L          ����?
X          ����?
Y          ����?      @      	   �  `   
F          ����?
E          ����?
S          ����?
T          ����?      @      	   b  `   
>          ����?
=          ����?
M          ����?
N          ����?      @      	   �  `   
5          ����?
4          ����?
F          ����?
G          ����?      @      	   �  `   
,          ����?
+          ����?
>          ����?
?          ����?      @      	   3  O   
#          ����?
5          ����?
6          ����?      @   	   	   �  O   
[          ����?
Z          ����?
a          ����?      @       	   �  `   
W          ����?
V          ����?
^          ����?
_          ����?      @      	   &  `   
R          ����?
Q          ����?
[          ����?
\          ����?      @      	   �  `   
L          ����?
K          ����?
W          ����?
X          ����?      @      	   \  `   
E          ����?
D          ����?
R          ����?
S          ����?      @      	   �  `   
=          ����?
<          ����?
L          ����?
M          ����?      @      	   �  `   
4          ����?
3          ����?
E          ����?
F          ����?      @      	   -  `   
+          ����?
*          ����?
=          ����?
>          ����?      @      	   �  `   
#          ����?
"          ����?
4          ����?
5          ����?      @      	   c  O   
          ����?
+          ����?
,          ����?      @   	   	     O   
V          ����?
U          ����?
^          ����?      @       	   �  `   
Q          ����?
P          ����?
Z          ����?
[          ����?      @      	   V  `   
K          ����?
J          ����?
V          ����?
W          ����?      @      	   �  `   
D          ����?
C          ����?
Q          ����?
R          ����?      @      	   �  `   
<          ����?
;             �?
K          ����?
L          ����?      @      	   '  `   
3          ����?
2             �?
D          ����?
E          ����?      @      	   �  `   
*          ����?
)          ����?
<          ����?
=          ����?      @      	   ]  `   
"          ����?
!          ����?
3          ����?
4          ����?      @      	   �  `   
          ����?
          ����?
*          ����?
+          ����?      @      	   �  O   
          ����?
"          ����?
#          ����?      @   	   	   ?  O   
P          ����?
O          ����?
Z          ����?      @       	   �  `   
J          ����?
I          ����?
U          ����?
V          ����?      @      	   �  `   
C          ����?
B          ����?
P          ����?
Q          ����?      @      	   !  `   
;             �?
:          ����?
J          ����?
K          ����?      @      	   �  a   
2             �?
1             �?
C             �?
D             �?      Y@      	   V  a   
)             �?
(             �?
;             �?
<             �?      Y@      	   �  `   
!          ����?
           ����?
2             �?
3          ����?      @      	   �  `   
          ����?
          ����?
)          ����?
*          ����?      @      	   &  `   
          ����?
          ����?
!          ����?
"          ����?      @      	   �  O   
          ����?
          ����?
          ����?      @   	   	   m  O   
I          ����?
H          ����?
U          ����?      @       	     `   
B          ����?
A          ����?
O          ����?
P          ����?      @      	   �  `   
:          ����?
9          ����?
I          ����?
J          ����?      @      	   O  `   
1             �?
0          ����?
B          ����?
C          ����?      @      	   �  a   
(             �?
'             �?
:             �?
;             �?      Y@      	   �  a   
              �?
             �?
1             �?
2             �?      Y@      	     `   
          ����?
          ����?
(             �?
)          ����?      @      	   �  `   
          ����?
          ����?
           ����?
!          ����?      @      	   T  `   
          ����?
          ����?
          ����?
          ����?      @      	   �  O   
	          ����?
          ����?
          ����?      @   	   	   �  O   
A          ����?
@          ����?
O          ����?      @       	   G  `   
9          ����?
8          ����?
H          ����?
I          ����?      @      	   �  `   
0          ����?
/          ����?
A          ����?
B          ����?      @      	   }  `   
'          ����?
&          ����?
9          ����?
:          ����?      @      	     `   
          ����?
          ����?
0          ����?
1             �?      @      	   �  `   
          ����?
          ����?
'          ����?
(             �?      @      	   N  `   
          ����?
          ����?
          ����?
           ����?      @      	   �  `   
          ����?
          ����?
          ����?
          ����?      @      	   �  `   
	          ����?
          ����?
          ����?
          ����?      @      	     O   
          ����?
          ����?
          ����?      @   	   	   �
  O   
8          ����?
7          ����?
H          ����?      @       	   w
  `   
/          ����?
.          ����?
@          ����?
A          ����?      @      	   
  `   
&          ����?
%          ����?
8          ����?
9          ����?      @      	   �	  `   
          ����?
          ����?
/          ����?
0          ����?      @      	   H	  `   
          ����?
          ����?
&          ����?
'          ����?      @      	   �  `   
          ����?
          ����?
          ����?
          ����?      @      	   ~  `   
          ����?
          ����?
          ����?
          ����?      @      	     `   
          ����?
          ����?
          ����?
          ����?      @      	   �  `   
          ����?
          ����?
          ����?
          ����?      @      	   O  O   
          ����?
          ����?
	          ����?      @   	   	   �  O   
.          ����?
-          ����?
@          ����?      @       	   �  `   
%          ����?
$          ����?
7          ����?
8          ����?      @      	   B  `   
          ����?
          ����?
.          ����?
/          ����?      @      	   �  `   
          ����?
          ����?
%          ����?
&          ����?      @      	   x  `   
          ����?
          ����?
          ����?
          ����?      @      	     `   
          ����?

          ����?
          ����?
          ����?      @      	   �  `   
          ����?
          ����?
          ����?
          ����?      @      	   I  `   
          ����?
          ����?
          ����?
          ����?      @      	   �  `   
          ����?
          ����?
          ����?
          ����?      @      	     O   
           ����?
          ����?
          ����?      @   	   	   +  >   
$          ����?
7          ����?      @	       	   �  O   
          ����?
-          ����?
.          ����?      @	      	   �  O   
          ����?
$          ����?
%          ����?      @	      	   @  O   
          ����?
          ����?
          ����?      @	      	   �  O   

          ����?
          ����?
          ����?      @	      	   �  O   
          ����?
          ����?
          ����?      @	      	   D  O   
          ����?

          ����?
          ����?      @	      	   �   O   
          ����?
          ����?
          ����?      @	      	   �   O   
           ����?
          ����?
          ����?      @	      	   H   >   
          ����?
          ����?      @	   	   	      @ -          -         w @ -          -         w @       w #         � h  Z&  I&  &  &  �%  �%  �%  �%  o%  ^%  M%  %  
%  �$  �$  �$  �$  s$  b$  Q$  $  $  �#  �#  �#  �#  w#  f#  4#  ##  #  �"  �"  �"  �"  {"  j"  Y"  H"  "  "  �!  �!  �!  �!  �!  ~!  L!  ;!  *!  !  �   �   �   �   �   q   `   O         �  �  �  �  �  d  S  B    �  �  �  �  �  �  x  F  5  $    �  �  �  �  |  k  Z  I      �  �  �  �  �    M  <  +    �  �  �  �  �  r  @  /      �  �  �  �  v  e  T  C       �  �  �  �  �  y  G  6  %    �  �  �  �  }  l  [  J      �  �  �  �  p  _  N  =    �  �  �  �  �  �  s  @  /      �  �  �  �  u  d  S  B    �  �  �  �  �  �  x  F  5  $  �  �  �  �  �  |  k  9  (      �  �  �  �  n  ]  L  ;    �  �  �  �  �  �  p  >  -      �  �  �  �  t  c  R       �  �  �  �  �  g  V  E  4    �  �  �  �  �  {  j  8  '      �  �  �  �  n  ]  L  ;  	  �  �  �  �  �  �  P  ?  .  �  �  �  �  �  �  u  d  2  !    �
  �
  �
  �
  �
  h
  W
  F
  5
  
  �	  �	  �	  �	  �	  |	  k	  9	  (	  	  	  �  �  �  �  o  ^  ,    
  �  �  �  �  �  b  Q  @  /  �  �  �  �  �  �  v  e  3  "       �  �  �  �  i  X  G  6    �  �  �  �  m  \  K      �  �  �  �  q  `  O      �  �  �  �  u  d  S  !    �  �  �                  
�                  {               e                O      " " "HF& "" "HF&{� �                          �    "  3! 4 .      @N`�              �            	   �    {v           
   p    "  3! 4 .      @I" �@( " " 	I&"  " 	I&" �� �            �               �            	   k    {P           
   J    @( " " 	I&"  " 	I&" �� �         	�                  �    "  " G 3! 4 .   ����?N`�              �               �            	   w    @!  "  " G&w" "  F" G& {"    =& {-          -         { �         	