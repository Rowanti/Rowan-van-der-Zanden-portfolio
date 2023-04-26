module Opdracht2 where
    -- import Data.Bits
    import Data.Char

    --1a
    euclid::Integer->Integer->Integer
    -- euclid x y = maximum [c| c<-[1..x],x `mod` c == 0 && y `mod` c==0]
    euclid x y
        | x `mod` y > 0 = euclid y (x `mod` y)
        | otherwise = y

    --1b
    egcd :: Integer -> Integer -> (Integer,Integer,Integer)
    egcd 0 b = (b, 0, 1)
    egcd a b =
        let (g, s, t) = egcd (b `mod` a) a
        in (neg g modulo, neg(t - (b `div` a) * s) modulo, neg s modulo)
        where modulo = a `mod` b
    
    -- neg::Integer -> Integer -> Integer
    -- neg x m
    --     | x < 0 = x + m
    --     | otherwise = x


    neg::Integer -> Integer -> Integer
    neg x m
        | x < 0 = neg (x + m) m -- erbij optellen tot hij pos is
        | otherwise = x

    --2 
    modulus::Integer -> Integer -> Integer
    modulus p q = p*q

    modulusAccent::Integer -> Integer -> Integer
    modulusAccent p q = (p-1)*(q-1)

    privateKey:: Integer -> Integer
    privateKey ma = head [a |a<-[100..ma-1], euclid a ma == 1]

    publicKey:: Integer -> Integer -> Integer
    publicKey e ma = head [d | d <- [100..], (e * d) `mod` ma == 1]

    generateKey::Integer ->Integer -> (Integer, Integer, Integer)
    generateKey p q = (e,d,m)
        where
            ma = modulusAccent p q
            e = privateKey ma
            d = publicKey e ma
            m = modulus p q
    --3a
    rsaencrypt::(Integer, Integer) -> Integer -> Integer
    rsaencrypt (e,m) x = x^e `mod` m

    --3b
    rsadecrypt::(Integer, Integer) -> Integer -> Integer
    rsadecrypt (d,m) x = x^d `mod` m

    --4
    p = 101
    q = 107
    encrypt::Char -> Integer
    encrypt x = rsaencrypt (e,m) (toInteger (fromEnum x))
        where (e,d,m) = generateKey p q
    
    decrypt::Integer -> Char
    decrypt x = chr(fromInteger(rsadecrypt (d,m) x))
        where (e,d,m) = generateKey p q
    
    --5
    {-
    Bob genereerd een sleutelpaar met twee priemgetallen.
    Bob stuurt zijn pulieke sluitel naar Alice.
    Alice genereerd ook een sleutelpaar.
    De publieke sleutel van Alice wordt naar Bob gestuurd deze wordt ge-encrypten met
    de publieke sluitel van Bob.
    Bob kan dit bericht decrypten met zijn privé sleutel.
    Op deze manier kunnen Bob en Alice berichten naar elkaar sturen op een veilige manier.
    -}