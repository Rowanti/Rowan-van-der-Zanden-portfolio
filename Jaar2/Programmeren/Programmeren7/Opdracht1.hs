module Opdracht1 where
    import Data.Bits
    --1a
    faca::Int->Int
    faca 0 = 1
    faca n = n*faca(n-1)

    --1b
    facb::Int->Int
    facb x 
        | x== 0 = 1
        |otherwise = product [1..x]
    
    --2a
    nulpuntena::Double->Double->Double->[Double]
    nulpuntena a b c 
        | (b^2-4*a*c) < 0 = []
        | (b^2-4*a*c) == 0 = [(-b)/(2*a)]
        | otherwise = [(-b+sqrt(b^2-4*a*c))/(2*a),(-b-sqrt(b^2-4*a*c))/(2*a)]
    
    --2b
    nulpuntenb::Double->Double->Double->[Double]
    nulpuntenb a b c 
        | discriminant<0 = []
        | discriminant == 0 = [(-b+sqrt(discriminant))/(2*a)]
        | otherwise = [(-b+sqrt(discriminant))/(2*a),(-b-sqrt(discriminant))/(2*a)]
        where discriminant = b^2 - 4*a*c
    --2c
    dobbelsteen::[(Int,Int,Int)]
    dobbelsteen = [(x,y,z)|x<-[1..6],y<-[1..x],z<-[1..y],(x+y+z) `mod` 5==0]

    --2d
    dobbelsteenb::Int->[(Int,Int,Int)]
    dobbelsteenb n = [(x,y,z)|x<-[1..6],y<-[1..x],z<-[1..y],(x+y+z) `mod` n==0]

    --3
    puzzle::[(Int, Int, Int)]
    puzzle = [(a,b,c)|a<-[(-100)..100],b<-[(-100)..100],c<-[(-100)..100],(2*(b-c))==a,(a*c)==b,(a+b)`div`2==c]
    
    -- 4a 
    -- stack overflow at 9999999*9, tweede number kan veel groter
    mult::Integer->Integer->Integer
    mult a b
        | a < 1 = 0
        | otherwise = b + mult (a-1) b
    
    -- 4b
    fastmult :: Integer -> Integer -> Integer
    fastmult x y
        | y == 0    = 0
        | even y    = fastmult (x `shiftL` 1) (y `shiftR` 1)
        | otherwise = x + fastmult (x `shiftL` 1) (y `shiftR` 1) 


    -- 5a
    pow :: Integer -> Integer -> Integer
    pow x p
        | p == 0    = 1
        | even p    = y * y
        | otherwise = x * y * y
        where
        y = pow x (p `div` 2)
    -- 5b
    fastpow :: Integer -> Integer -> Integer
    fastpow x p
      | p == 0          = 1
      | p `mod` 2 == 0  = fastpow (fastmult x x) (p `shiftR` 1)
      | otherwise       = fastmult x (fastpow (fastmult x x) (p `shiftR` 1))
