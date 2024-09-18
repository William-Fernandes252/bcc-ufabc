inits :: [a] -> [[a]]
inits x = foldr (\i o -> o ++ [take (length o) x]) [[]] x

-- >>> inits "ate"
-- ["","a","at","ate"]
