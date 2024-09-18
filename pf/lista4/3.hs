minlistr :: [Int] -> Int
minlistr = foldr1 (\i acc -> min i acc)

-- >>> minlistr [1, 2, 3]
-- 1

minlistl :: [Int] -> Int
minlistl = foldl1 (\acc i -> min i acc)

-- >>> minlistl [1, 2, 3]
-- 1
