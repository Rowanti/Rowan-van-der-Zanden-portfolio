module Opdracht3 where
    import Data.List

    --Opdracht 1.a
    differentieer :: (Double -> Double) -> Double -> Double -> Double
    differentieer f p x = (f (x + p) - f (x - p)) / (2 * p)

    --Opdracht 1.b
    integreer::(Double->Double)->Double->Double->Double->Double
    integreer f a b p = sum $ map ((p*).differentieer f p) [a,a+p..b]


    --2 
    dubbelen::[Int]->[Int]
    dubbelen = nub
    
    --3
    allRolls :: [[Int]]
    allRolls = [[a,b,c,d,e] | a <- [1..6], b <- [1..6], c <- [1..6], d <- [1..6], e <- [1..6]]

    isStraight :: [Int] -> Bool
    isStraight roll = sortedRoll == [1,2,3,4,5] || sortedRoll == [2,3,4,5,6]
        where sortedRoll = sort roll

    isPoker :: [Int] -> Bool
    isPoker roll = all (== head roll) (tail roll)

    showHand :: [Int] -> Int
    showHand roll
        | isPoker roll = 1
        | isStraight roll = 2
        | length (group roll) == 2 = if length (head $ group roll) == 1 then 3 else 4
        | length (group roll) == 3 = if length (head $ group roll) == 3 then 5 else 6
        | length (group roll) == 4 = 7
        | otherwise = 8
    
    isSimilar::Int->Int->Bool
    isSimilar a b
        | a==b = True
        |otherwise = False

    callculateChance::Int->Double
    callculateChance a = (fromIntegral (length newlist) / fromIntegral (length allRolls)) *100
        where
            newlist = filter (\x -> showHand x == a) allRolls
    
    -- 1 = Poker            0.077 %
    -- 2 = Straigth         3.086 %
    -- 3 = Four of a kind   0.386 %
    -- 4 = Full house       1.157 %
    -- 5 = Three of a kind  1.929 %
    -- 6 = Two pair         9.645 %
    -- 7 = One pair         38.580 %
    -- 8 = Bust             45,139 %