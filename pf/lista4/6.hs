filterr :: (a -> Bool) -> [a] -> [a]
filterr p xs = foldr (\i o -> if p i then i : o else o) [] xs

-- >>> filterr even [1, 2, 3]
-- [2]

filterl :: (a -> Bool) -> [a] -> [a]
filterl p xs = foldl (\o i -> if p i then o ++ [i] else o) [] xs

-- >>> filterl (not . even) [1, 2, 3]
-- [1,3]
