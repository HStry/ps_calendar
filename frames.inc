
/IsFrame  {IsDict+ {dup (ObjectType) known {(ObjectType) get (FrameType) eq} {pop false} ifelse} {pop false} ifelse} bind def
/IsFrame+ {dup IsFrame} bind def




/Margin  {1 get} def
/Padding {2 get} def
/Left    {0 get} def
/Right   {1 get} def
/Bottom  {2 get} def
/Top     {3 get} def

/ExtX      {0 get 0 get} def
/ExtY      {0 get 1 get} def
/ExtWidth  {0 get 2 get} def
/ExtHeight {0 get 3 get} def
/ExtXmax   {dup ExtX exch ExtWidth  add} def
/ExtYmax   {dup ExtY exch ExtHeight add} def

/BdrX      {dup ExtX exch Margin Left   add} def
/BdrY      {dup ExtY exch Margin Bottom add} def
/BdrWidth  {dup ExtWidth  exch dup Margin Left   exch Margin Right add sub} def
/BdrHeight {dup ExtHeight exch dup Margin Bottom exch Margin Top   add sub} def
/BdrXmax   {dup ExtXmax exch Margin Right sub} def
/BdrYmax   {dup ExtYmax exch Margin Top   sub} def

/IntX      {dup BdrX exch Padding Left   add} def
/IntY      {dup BdrY exch Padding Bottom add} def
/IntWidth  {dup BdrWidth  exch dup Padding Left   exch Padding Right add sub} def
/IntHeight {dup BdrHeight exch dup Padding Bottom exch Padding Top   add sub} def




/IntXmax   {dup BdrXmax exch Padding Right sub} def
/IntYmax   {dup BdrYmax exch Padding Top   sub} def


/FrameDef {
    4 dict begin
    
} def

/FrameSpacingDef {
    IsNull+ {pop 0} if
    [ exch IsInt+ {dup dup dup} {{IsNull+ {pop 0} if} forall} ifelse ]
} bind def

/ExtFrameDef {} bind def
/MidFrameDef {} bind def
/IntFrameDef {} bind def

/NestedFrameDef {} bind def


/FrameDef { % <x> <y> <width> <height> <[margin]> <[padding]> <origin>
    8 dict begin
    /Origin  exch def
    /Padding exch def
    /Margin  exch def
    /Height  exch def
    /Width   exch def
    /Y       exch def
    /X       exch def
    
    /Var     null def
    
    Padding IsNull {/Padding [0 0 0 0] def} if pop
    Margin  IsNull {/Margin  [0 0 0 0] def} if pop
    Padding IsInt  {/Var Padding def /Padding [Var Var Var Var] def} if pop
    Margin  IsInt  {/Var Margin  def /Margin  [Var Var Var Var] def} if pop
    
    Origin INT eq {
        /X      Margin  Left   sub
                Padding Left   sub def
        /Y      Margin  Bottom sub
                Padding Bottom sub def
        /Width  Margin  Left   add
                Margin  Right  add
                Padding Left   add
                Padding Right  add def
        /Height Margin  Bottom add
                Margin  Top    add
                Padding Bottom add
                Padding Top    add def
    } if
    Origin BDR eq {
        /X      Margin  Left   sub def
        /Y      Margin  Bottom sub def
        /Width  Margin  Left   add
                Margin  Right  add def
        /Height Margin  Bottom add
                Margin  Top    add def
    } if
    %Origin EXT eq {  % Just assume this is the case if not INT/BDR
    %} if
    
    [[X Y Width Height] Margin Padding]
    end
} def

/BorderPath {
    2 dict begin
    /Selection exch def
    /Frame exch def
    
    Frame BdrX    Frame BdrY    moveto
    Frame BdrXmax Frame BdrY    Selection Bottom {lineto} {moveto} ifelse
    Frame BdrXmax Frame BdrYmax Selection Right  {lineto} {moveto} ifelse
    Frame BdrX    Frame BdrYmax Selection Top    {lineto} {moveto} ifelse
    Frame BdrX    Frame BdrY    Selection Left   {lineto} {moveto} ifelse
    
    end
} def


/MonthNames [
    [(January)   (February)  (March)     (April)     (May)       (June)
     (July)      (August)    (September) (October)   (November)  (December)]
    [(Jan)       (Feb)       (Mar)       (Apr)       (May)       (Jun)
     (Jul)       (Aug)       (Sep)       (Oct)       (Nov)       (Dec)]
] def

/DayNames [
    [(Monday)    (Tuesday)   (Wednesday) (Thursday)  (Friday)    (Saturday)  (Sunday)]
    [(Mon)       (Tue)       (Wed)       (Thu)       (Fri)       (Sat)       (Sun)]
    [(Mo)        (Tu)        (We)        (Th)        (Fr)        (Sa)        (Su)]
] def

/MonthName {MonthNames exch get exch 1 sub get} def
/DayName   {DayNames   exch get exch       get} def

