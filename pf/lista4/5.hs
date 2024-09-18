remove :: String -> String -> String
remove x y = foldr (\i o -> if elem i x then o else i : o) [] y

-- >>> remove "first" "second"
-- "econd"
