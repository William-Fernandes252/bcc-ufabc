newtype Box a = Box a deriving (Eq, Show)

instance Functor Box where
  fmap :: (a -> b) -> Box a -> Box b
  fmap f (Box x) = Box $ f x

instance Applicative Box where
  pure :: a -> Box a
  pure = Box
  (<*>) :: Box (a -> b) -> Box a -> Box b
  Box f <*> bx = fmap f bx

instance Monad Box where
  (>>=) :: Box a -> (a -> Box b) -> Box b
  (Box x) >>= f = f x

data Expr a = Var a | Val Int | Add (Expr a) (Expr a) deriving Show

instance Functor Expr where
  fmap :: (a -> b) -> Expr a -> Expr b
  fmap f (Var x) = Var $ f x
  fmap f (Add e1 e2) = Add (fmap f e1) (fmap f e2)

instance Applicative Expr where
  pure :: a -> Expr a
  pure = Var
  (<*>) :: Expr (a -> b) -> Expr a -> Expr b
  (Var f) <*> vx = fmap f vx

instance Monad Expr where
  return = pure
  (>>=) :: Expr a -> (a -> Expr b) -> Expr b
  (Var x) >>= f = f x
  (Add e1 e2) >>= f = Add (e1 >>= f) (e2 >>= f)

newtype Identity a = Identity a
data Pair a = Pair a a

instance Functor Identity where
  fmap f (Identity a) = Identity (f a)

instance Applicative Identity where
  pure = Identity
  Identity f <*> i = fmap f i

instance Monad Identity where
  return = pure
  (Identity x) >>= f = f x

instance Functor Pair where
  fmap f (Pair a b) = Pair (f a) (f b)

instance Applicative Pair where
  pure x = Pair x x
  (Pair f _) <*> p = fmap f p

instance Monad Pair where
  return = pure
  (Pair x _) >>= f = f x

data Ghost a = Ghost

instance Functor Ghost where
  fmap f Ghost = Ghost

instance Applicative Ghost where
  pure _ = Ghost
  Ghost <*> Ghost = Ghost

instance Monad Ghost where
  Ghost >>= _ = Ghost

data Duo a where
  Duo :: (Bool -> a) -> Duo a

instance Functor Duo where
  fmap :: (a -> b) -> Duo a -> Duo b
  fmap f (Duo g) = Duo $ f.g

instance Applicative Duo where
  pure :: a -> Duo a
  pure x = Duo $ const x
  Duo f <*> (Duo x) = Duo $ \b -> f b (x b)

instance Monad Duo where
  return = pure
  (Duo g) >>= f = f $ g True

data Request a = Loading | Error | Success a

instance Functor Request where
  fmap f (Success a) = Success $ f a
  fmap _ Loading = Loading
  fmap _ Error = Error

instance Applicative Request where
  pure = Success
  Error <*> _ = Error
  _ <*> Error = Error
  _ <*> Loading = Loading
  (Success f) <*> sx = fmap f sx

instance Monad Request where
  Error >>= _ = Error
  Loading >>= _ = Loading
  Success x >>= f = f x

data Pocket a = One a | Two a a | Tree a a a deriving Show

instance Functor Pocket where
  fmap f (One x) = One $ f x
  fmap f (Two x y) = Two (f x) (f y)
  fmap f (Tree x y z) = Tree (f x) (f y) (f z)

value :: Pocket a -> a
value (One x) = x
value (Two _ x) = x
value (Tree _ _ x) = x

instance Eq a => Eq (Pocket a) where
  p1 == p2 = value p1 == value p2

instance Applicative Pocket where
  pure = One
  p1 <*> p2 = pure $ value p1 $ value p2

instance Monad Pocket where
  p >>= f = f $ value p

type Name = [Char]

type Weight = Double

type Height = Double

type IMC = Double

maybeIMC :: (Maybe Name, Maybe Weight, Maybe Height) -> Maybe IMC
maybeIMC (_, maybeWeight, maybeHeight) = do
  weight <- maybeWeight
  height <- maybeHeight
  return $ weight / (height ^ 2)

imc :: [(Maybe Name, Maybe Weight, Maybe Height)] -> Maybe [IMC]
imc = traverse maybeIMC

blue :: Monad m => m (m a) -> m a
blue m = m >>= id

yellow :: Monad m => (a -> b) -> m a -> m b
yellow f ma = f <$> ma

red :: Monad m => (a -> b -> c) -> m a -> m b -> m c
red f ma mb = (f <$> ma) <*> mb

green :: Monad m => m a -> m (a -> b) -> m b
green ma mf = mf <*> ma

orange :: Monad m => [m a] -> m [a]
orange = traverse (>>=return)

purple :: Monad m => [a] -> (a -> m b) -> m [b]
purple xs f = traverse ((>>=return) . f) xs

newtype ChangeList a = ChangeList { runChangeList :: [Int] -> ([Int], a)}

unstack :: ChangeList Int
unstack = ChangeList $ \(x:xs) -> (xs, x)

stack :: Int -> ChangeList ()
stack x = ChangeList $ \xs -> (x : xs, ())

instance Functor ChangeList where
  fmap f (ChangeList g) = ChangeList $ \xs -> fmap f (g xs)

-- >>> let showUnstack = fmap show unstack
-- >>> runChangeList showUnstack [4, 5, 6]
-- ([5,6],"4")

instance Applicative ChangeList where
  pure x = ChangeList $ \xs -> (xs, x)
  ChangeList fx <*> ChangeList f = 
    ChangeList $ \l ->
      let (l1, fab) = fx l
          (l2, a) = f l1
      in  (l2, fab a)


    

-- >>> :t (fmap (+) unstack) <*> unstack
-- (fmap (+) unstack) <*> unstack :: ChangeList Int

unstackn n = ChangeList $ \xs -> (drop n xs, take n xs)

-- >>> runChangeList (unstackn 3) [1,2,3,4,5,6,7,8,9]
-- ([4,5,6,7,8,9],[1,2,3])

stackn xs = ChangeList $ \is -> (reverse xs ++ is, ())

-- >>> runChangeList (stackn [10,20,30]) [1,2,3]
-- ([30,20,10,1,2,3],())

