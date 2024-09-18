remdups :: Eq a => [a] -> [a]
remdups = foldr (\i o -> if length o > 0 && head o == i then o else i : o) []

-- >>> remdups [1, 2, 2, 2, 3, 3, 3, 1, 1]
-- [1,2,3,1]
