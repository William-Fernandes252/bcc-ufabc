-- | Successive approximations of `e`
sae :: Int -> [Double]
sae n = scanl (\acc i -> foldr1 (+) (map ((1/).fromIntegral.factorial) [0..i])) 0 [0..n]
    where
        factorial :: Int -> Int
        factorial 0 = 1
        factorial x = foldr (*) 1 [1..x]

-- >>> sae 20
-- [0.0,1.0,2.0,2.5,2.6666666666666665,2.708333333333333,2.716666666666667,2.7180555555555554,2.7182539682539684,2.7182787698412696,2.7182815255731922,2.7182818011463845,2.718281826198493,2.7182818282861687,2.718281828446759,2.7182818284582297,2.7182818284589945,2.718281828459042,2.718281828459045,2.718281828459045,2.718281828459045,2.718281828459045]