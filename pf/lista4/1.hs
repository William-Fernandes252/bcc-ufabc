sumsq :: Int -> Int
sumsq n = foldr (\i acc -> i * i + acc) 0 [1..n]

-- >>> sumsq 6
-- 91
