iterate' :: (a -> a) -> a -> [a]
iterate' f x = scanl (\acc i -> f acc) x (repeat ())

-- >>> take 10 $ iterate' (+1) 1
-- [1,2,3,4,5,6,7,8,9,10]
