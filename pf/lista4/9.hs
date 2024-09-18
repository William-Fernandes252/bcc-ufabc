approxe :: Int -> Float

approxe n = foldl (\acc i -> acc + 1 / fromIntegral (factorial i)) 0.0 [0..n]
    where
        factorial :: Int -> Int
        factorial 0 = 1
        factorial x = foldr (*) 1 [1..x]

-- >>> approxe 4
-- 2.7083335
