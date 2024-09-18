shift :: [a] -> [a]
shift [] = []
shift (x : xs) = xs ++ [x]

-- >>> shift [1, 2, 3, 4, 5]
-- [2,3,4,5,1]

rotate :: [a] -> [[a]]
rotate xs = foldl (\acc _ -> acc ++ [shift (last acc)]) [xs] (tail xs)

-- >>> rotate [1, 2, 3]
-- [[1,2,3],[2,3,1],[3,1,2]]
