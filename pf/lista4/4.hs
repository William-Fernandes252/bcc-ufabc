reverse' :: [a] -> [a]
reverse' = foldr (\i acc -> acc ++ [i]) []

-- >>> reverse' [1, 2, 3]
-- [3,2,1]
