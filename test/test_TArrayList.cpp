# include "arraylist.h"
# include "../gtest/gtest.h"

TEST(TArrayList, can_create_array_list) 
{
  ASSERT_NO_THROW(TArrayList<int> al(5));
}

TEST(TArrayList, can_copy_array_list) 
{
  TArrayList<int> al1(5);
  ASSERT_NO_THROW(TArrayList<int> al2(al1));
}

TEST(TArrayList, can_create_array_list_with_different_types)
{
  ASSERT_NO_THROW(TArrayList<char> al(5));
  ASSERT_NO_THROW(TArrayList<double> al(5));
  ASSERT_NO_THROW(TArrayList<unsigned int> al(5));
}

TEST(TArrayList, can_create_array_list_iterator)
{
  TArrayList<int> al(5);
  ASSERT_NO_THROW(TArrayListIterator<int> it(al));
}

TEST(TArrayList, can_copy_array_list_iterator) 
{
  TArrayList<int> al(5);
  TArrayListIterator<int> it1(al);

  ASSERT_NO_THROW(TArrayListIterator<int> it2 = it1);
}

TEST(TArrayList, can_del_array_list_iterator)
{
  TArrayList<int> al(5);

  al.InsFirst(5);

  TArrayListIterator<int> it(al, 0);

  ASSERT_NO_THROW(al.Del(it));
}

TEST(TArrayList, can_get_data_array_list_iterator)
{
  TArrayList<int> al(5);

  al.InsFirst(5);

  TArrayListIterator<int> it(al, 1);

  ASSERT_NO_THROW(it.GetData());
}

TEST(TArrayList, can_insert_first_and_last_elem) 
{
  TArrayList<int> al(5);

  ASSERT_NO_THROW(al.InsFirst(0));
  ASSERT_NO_THROW(al.InsLast(100));
}

TEST(TArrayList, can_get_first)
{
  TArrayList<int> al(5);
  al.InsFirst(0);

  EXPECT_EQ(0, al.GetFirst());
}

TEST(TArrayList, can_get_last)
{
  TArrayList<int> al(5);
  al.InsLast(99);
  al.InsLast(100);

  EXPECT_NE(99, al.GetLast());
  EXPECT_EQ(100, al.GetLast());
}

TEST(TArrayList, can_del_first)
{
  TArrayList<int> al(5);
  al.InsFirst(0);

  ASSERT_NO_THROW(al.DelFirst());
}

TEST(TArrayList, can_del_last)
{
  TArrayList<int> al(5);
  al.InsFirst(99);

  ASSERT_NO_THROW(al.DelLast());
}

TEST(TArrayList, array_list_full_check)
{
  TArrayList<int> al(5);

  EXPECT_EQ(al.IsFull(), false);
}

TEST(TArrayList, array_list_empty_check)
{
  TArrayList<int> al(5);

  EXPECT_EQ(al.IsEmpty(), true);
}

TEST(TArrayList, can_get_count_of_elem)
{
  TArrayList<int> al(5);

  al.InsFirst(0);
  al.InsFirst(1);
  al.InsFirst(2);

  EXPECT_EQ(3, al.GetCount());
}

TEST(TArrayList, array_list_iterator_can_go_through_list)
{
  TArrayList<int> al(5);

  al.InsFirst(0);
  al.InsFirst(1);
  al.InsFirst(2);
  al.InsFirst(3);
  al.InsFirst(4);

  TArrayListIterator<int> it(al.begin());

  int i = 4;
  for (it; it != al.end(); ++it)
  {
    EXPECT_EQ(it.GetData(), i);
    i--;
  }
}
