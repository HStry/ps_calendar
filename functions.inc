/CHARS [ <00> <01> <02> <03> <04> <05> <06> <07> <08> <09> <0A> <0B> <0C> <0D> <0E> <0F>
         <10> <11> <12> <13> <14> <15> <16> <17> <18> <19> <1A> <1B> <1C> <1D> <1E> <1F>
         <20> <21> <22> <23> <24> <25> <26> <27> <28> <29> <2A> <2B> <2C> <2D> <2E> <2F>
         <30> <31> <32> <33> <34> <35> <36> <37> <38> <39> <3A> <3B> <3C> <3D> <3E> <3F>
         <40> <41> <42> <43> <44> <45> <46> <47> <48> <49> <4A> <4B> <4C> <4D> <4E> <4F>
         <50> <51> <52> <53> <54> <55> <56> <57> <58> <59> <5A> <5B> <5C> <5D> <5E> <5F>
         <60> <61> <62> <63> <64> <65> <66> <67> <68> <69> <6A> <6B> <6C> <6D> <6E> <6F>
         <70> <71> <72> <73> <74> <75> <76> <77> <78> <79> <7A> <7B> <7C> <7D> <7E> <7F>
         <80> <81> <82> <83> <84> <85> <86> <87> <88> <89> <8A> <8B> <8C> <8D> <8E> <8F>
         <90> <91> <92> <93> <94> <95> <96> <97> <98> <99> <9A> <9B> <9C> <9D> <9E> <9F>
         <A0> <A1> <A2> <A3> <A4> <A5> <A6> <A7> <A8> <A9> <AA> <AB> <AC> <AD> <AE> <AF>
         <B0> <B1> <B2> <B3> <B4> <B5> <B6> <B7> <B8> <B9> <BA> <BB> <BC> <BD> <BE> <BF>
         <C0> <C1> <C2> <C3> <C4> <C5> <C6> <C7> <C8> <C9> <CA> <CB> <CC> <CD> <CE> <CF>
         <D0> <D1> <D2> <D3> <D4> <D5> <D6> <D7> <D8> <D9> <DA> <DB> <DC> <DD> <DE> <DF>
         <E0> <E1> <E2> <E3> <E4> <E5> <E6> <E7> <E8> <E9> <EA> <EB> <EC> <ED> <EE> <EF>
         <F0> <F1> <F2> <F3> <F4> <F5> <F6> <F7> <F8> <F9> <FA> <FB> <FC> <FD> <FE> <FF> ] bind def
/Chr {CHARS exch get} bind def
/IsNull  {type /nulltype eq} bind def
/IsBool  {type /booltype eq} bind def
/IsInt   {type /integertype eq} bind def
/IsFloat {type /realtype eq} bind def
/IsStr   {type /stringtype eq} bind def
/IsArr   {type /arraytype eq} bind def
/IsDict  {type /dicttype eq} bind def

/IsNull+  {dup IsNull} bind def
/IsBool+  {dup IsBool} bind def
/IsInt+   {dup IsInt} bind def
/IsFloat+ {dup IsFloat} bind def
/IsStr+   {dup IsStr} bind def
/IsArr+   {dup IsArr} bind def
/IsDict+  {dup IsDict} bind def

/++ {1 add} bind def
/-- {1 sub} bind def

/nAdd  {-- {add} repeat} bind def
/nSub  {-- nAdd sub} bind def
/nAdd+ {dup ++ copy nAdd exch pop} bind def
/nSub+ {dup ++ copy nSub exch pop} bind def

/Add+  {2 copy add} bind def
/Sub+  {2 copy sub} bind def

/Push  {++  1 roll} bind def
/Pull  {++ -1 roll} bind def
/Swap  {dup Pull 2 Push -- Push} bind def

/nPop  {{pop} repeat} bind def

/mnPop {exch 2 add exch {dup Pull pop} repeat pop} bind def

/nArray  {++ [ exch 1 roll ] } bind def
/mnArray {++ 2 nAdd+ [ exch 2 add 1 roll 1 index add exch roll ] } bind def

/AZip+ {2 copy length exch length min dup array exch 0 exch {2 copy dup [ exch dup 8 index exch get exch 7 index exch get ] put ++ } repeat pop} bind def
/AZip  {AZip+ 1 2 mnPop} bind def

/DZip  { AZip << exch {aload pop} forall >> } bind def
/DZip+ { AZip+ << exch {aload pop} forall >> } bind def

/ALen   { [ exch {length} forall ] } bind def
/ASum   { 0 exch {add} forall } bind def
/ACSum  { [ exch 0 exch {add dup} forall pop ] } bind def

/ALen+  {dup ALen} bind def
/ASum+  {dup ASum} bind def
/ACSum+ {dup ACum} bind def

/AStrSplit  { [ exch {Chr} forall ] } bind def
/AStrJoin   {ALen+ ASum string exch ALen+ ACSum [ exch 0 exch aload 2 nPop ] exch AZip {1 index exch aload pop putinterval} forall} bind def
/AStrSplit+ {dup AStrSplit} bind def
/AStrJoin+  {dup AStrJoin} bind def

/StackInvert   { 1 sub 3 exch { dup -1 roll exch ++ } repeat pop } bind def
/ArrayInvert   { [ exch aload pop counttomark StackInvert ] } bind def
/StringInvert  { AStrSplit ArrayInvert AStrJoin } bind def

/StackInvert+  {dup StackInvert} bind def
/ArrayInvert+  {dup ArrayInvert} bind def
/StringInvert+ {dup StringInvert} bind def

/ExpSplit    { [ 3 1 roll {1 index 0 eq {exit} if 2 copy mod 3 1 roll exch 1 index idiv exch} loop 2 nPop ] ArrayInvert} bind def
/ExpSplit10  {10 ExpSplit} bind def
/ExpSplit+   {1 index exch ExpSplit} bind def
/ExpSplit10+ {dup ExpSplit10} bind def

/NumStr { [ exch dup 0 lt {abs (-) exch} if 10 ExpSplit {48 add Chr} forall ] AStrJoin } bind def
/ZPad   { [ 3 1 roll exch (-) anchorsearch {3 StackInvert} {exch} ifelse 1 index length sub 0 max {(0) exch} repeat ] AStrJoin } bind def

/Params { dup length 1 exch mnArray DZip } bind def

/Font { findfont exch scalefont setfont } def
