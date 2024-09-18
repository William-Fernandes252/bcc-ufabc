lengthr :: [a] -> Int
lengthr = foldr (\_ acc -> acc + 1) 0

-- >>> lengthr [1, 2, 3] + lengthr []
-- 3

lengthl :: [a] -> Int
lengthl = foldl (\acc _ -> acc + 1) 0

-- >>> lengthl [1, 2, 3] + lengthl []
-- 3
