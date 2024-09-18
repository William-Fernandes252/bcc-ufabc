import qualified Text.Read as TR
import qualified Distribution.Compat.Prelude as TR
import Data.Monoid

data Result a = Score a | Plagiarism
    deriving (Eq, Ord, Show)

instance Functor Result where
    fmap _ Plagiarism = Plagiarism
    fmap f (Score x) = Score (f x)

instance Num a => Semigroup (Result a) where
    (Score a) <> (Score b) = Score (a + b)
    _ <> _ = Plagiarism

instance Num a => Monoid (Result a) where
    mempty :: Result a
    mempty = Score 0

getResult :: Result a -> a
getResult (Score a) = a

-- >>> foldMap Score [1, 2, 3 ,4]

-- >>> Score 1 <> Plagiarism
-- Plagiarism

data Set a = Set [a] deriving (Eq)

instance (Show a) => Show (Set a) where
  show :: (Show a) => Set a -> String
  show (Set a) = [if c == '[' then '{' else if c == ']' then '}' else c | c <- show a]

instance (Ord a) => Semigroup (Set a) where
  Set as <> Set bs = fromList $ as <> bs

instance (Ord a) => Monoid (Set a) where
  mempty = Set []

-- >>> show (Set [1, 2, 3])
-- "{1,2,3}"

fromList :: (Ord a) => [a] -> Set a
fromList xs = Set $ foldr (\i acc -> if i `elem` acc then acc else i : acc) [] xs

-- >>> fromList [1, 2, 3, 3, 3]
-- {1,2,3}

member :: (Ord a) => a -> Set a -> Bool
member x (Set xs) = x `elem` xs

-- >>> member 9 (fromList [1, 2, 3, 3])
-- False

insert :: (Ord a) => a -> Set a -> Set a
insert x (Set xs) = if member x (Set xs) then Set xs else Set (x : xs)

-- >>> insert 9 $ fromList [1, 2, 3, 3, 3]
-- {9,1,2,3}

delete :: (Ord a) => a -> Set a -> Set a
delete x (Set xs) = if not $ member x (Set xs) then Set xs else Set $ filter (/= x) xs

-- >>> delete 1 $ fromList [1, 2, 3, 3, 3]
-- {2,3}

data Diet = Vegan | Vegetarian | Traditional deriving (Eq, Enum, Show)

data Meal = Meal (Set String) Int Diet deriving (Eq, Show)

instance Semigroup Diet where
  a <> b = toEnum $ max (fromEnum a) (fromEnum b)

instance Monoid Diet where
  mempty = Vegan

instance Semigroup Meal where
  (Meal ingredientsA priceA dietA) <> (Meal ingredientsB priceB dietB) = Meal (ingredientsA <> ingredientsB) (priceA + priceB) (dietA <> dietB)

-- >>> (Meal (Set ["pasta", "chicken"]) 10 Traditional) <> (Meal (Set ["soy meat", "cucumber"]) 10 Vegan)
-- Meal {"pasta","chicken","soy meat","cucumber"} 20 Traditional

data Tree a = Leaf a | Node (Tree a) a (Tree a) deriving Show

instance Functor Tree where
  fmap f (Leaf a) = Leaf (f a)
  fmap f (Node l v r) = Node (fmap f l) (f v) (fmap f r)

instance Foldable Tree where
  foldMap f (Leaf x) = f x
  foldMap f (Node l v r) = foldMap f l `mappend` f v `mappend` foldMap f r

search :: (Eq a) => a -> Tree a -> Bool
search a t = case t of
  Leaf x -> x == a
  Node l v r -> a == v || search a l || search a r

countLetters :: Tree String -> Tree Int
countLetters t = fmap length t

-- >>> countLetters (Leaf "test")
-- Leaf 4

convertString2Int :: String -> Maybe Int
convertString2Int = TR.readMaybe

-- >>> convertString2Int "test"
-- Nothing

nothingToZero :: Num a => Maybe a -> a
nothingToZero Nothing = 0
nothingToZero (Just i) = i

-- >>> nothingToZero $ convertString2Int "2"
-- 2

frutasDaArvore :: Tree String -> Int
frutasDaArvore = getSum . foldMap (Sum . nothingToZero . convertString2Int)

-- >>> frutasDaArvore (Leaf "2")
-- 2

newtype ZipList a = Z [a] deriving Show

instance Functor ZipList where
  fmap g (Z xs) = Z $ fmap g xs

instance Applicative ZipList where
  pure x = Z (repeat x)
  Z fs <*> Z xs = Z [f x | (f, x) <- zip fs xs]

newtype Identity a = Identity a
data Pair a = Pair a a

instance Functor Identity where
  fmap f (Identity a) = Identity (f a)

instance Functor Pair where
  fmap f (Pair a b) = Pair (f a) (f b)

instance Applicative Identity where
  pure = Identity
  Identity f <*> i = fmap f i

instance Applicative Pair where
  pure x = Pair x x
  (Pair f _) <*> p = fmap f p