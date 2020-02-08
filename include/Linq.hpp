#include <algorithm>
#include <numeric>

namespace simlinq {

//Aggregate<TSource,TAccumulate,TResult>(IEnumerable<TSource>, TAccumulate, Func<TAccumulate,TSource,TAccumulate>, Func<TAccumulate,TResult>)
//Applies an accumulator function over a sequence. The specified seed value is used as the initial accumulator value, and the specified function is used to select the result value.
//Aggregate<TSource,TAccumulate>(IEnumerable<TSource>, TAccumulate, Func<TAccumulate,TSource,TAccumulate>)
//Applies an accumulator function over a sequence. The specified seed value is used as the initial accumulator value.

    /*
        Applies an accumulator function over a sequence.
    */
    template <typename container, typename aggregator>
    auto Aggregate(const container &c, aggregator &&agr) {
        typename container::value_type result;

        for (const auto &value : c)
        {
            agr(value, result);
        }

        return result;
    }

    /*
        Appends a value to the end of the sequence.
    */
    template <typename container>
    void Append(container &c, typename container::value_type &value) {
        // TODO: this is bad container-specific implementation; should be rewritten.
        container.push_back(value);
    }

    /*
        Computes the average of a sequence.
    */
    template <typename container, typename result_type = typename container::value_type>
    result_type Average(const container &c) {
        if (std::begin(c) == std::end(c))
            throw std::invalid_argument("Average: an empty array");

        result_type result;
        for (const auto &value : c)
        {
            result += c;
        }
        result /= std::size(c);
        return result;
    }

//Computes the average of a sequence of Single values.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Decimal>)
//Computes the average of a sequence of Decimal values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Double>)
//Computes the average of a sequence of Double values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Int32>)
//Computes the average of a sequence of Int32 values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Int64>)
//Computes the average of a sequence of Int64 values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Decimal>>)
//Computes the average of a sequence of nullable Decimal values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Double>>)
//Computes the average of a sequence of nullable Double values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int32>>)
//Computes the average of a sequence of nullable Int32 values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int64>>)
//Computes the average of a sequence of nullable Int64 values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Single>>)
//Computes the average of a sequence of nullable Single values that are obtained by invoking a transform function on each element of the input sequence.
//Average<TSource>(IEnumerable<TSource>, Func<TSource,Single>)
//Computes the average of a sequence of Single values that are obtained by invoking a transform function on each element of the input sequence.
//Cast<TResult>(IEnumerable)
//Casts the elements of an IEnumerable to the specified type.

//DefaultIfEmpty<TSource>(IEnumerable<TSource>)
//Returns the elements of the specified sequence or the type parameter's default value in a singleton collection if the sequence is empty.
//DefaultIfEmpty<TSource>(IEnumerable<TSource>, TSource)
//Returns the elements of the specified sequence or the specified value in a singleton collection if the sequence is empty.
//Distinct<TSource>(IEnumerable<TSource>)
//Returns distinct elements from a sequence by using the default equality comparer to compare values.
//Distinct<TSource>(IEnumerable<TSource>, IEqualityComparer<TSource>)
//Returns distinct elements from a sequence by using a specified IEqualityComparer<T> to compare values.
//ElementAt<TSource>(IEnumerable<TSource>, Int32)
//Returns the element at a specified index in a sequence.
//ElementAtOrDefault<TSource>(IEnumerable<TSource>, Int32)
//Returns the element at a specified index in a sequence or a default value if the index is out of range.

    /*
        Returns the first element of a sequence.
    */
    template <typename container>
    std::optional<typename container::value_type> First(const container &c) {
        using optional_type = std::optional<typename container::value_type>;
        std::begin(c) == std::end(c)
            ? optional_type()
            : optional_type(*(c.first()));
    }


    /*
        Returns the first element in a sequence that satisfies a specified condition.
    */
    template<typename container, unary_predicate condition>
    std::optional<typename container::value_type> First(const container& c, condition&& cond) {
        using optional_type = std::optional<typename container::value_type>;

        auto res = std::find_first_if(std::begin(c),
                                      std::end(c),
                                      cond);
        return res == std::end(c)
                ? optional_type()
                : optional_type(*res);
    }


    /*
        Returns the first element of a sequence, or a default value if the sequence contains no elements.
    */
    template<typename container>
    auto FirstOrDefault(const container& c) {
        std::begin(c) == std::end(c)
            ? typename container::value_type()
            : *(c.first());
    }


    /*
        Returns the first element of the sequence that satisfies a condition or a default value if no such element is found.
    */
    template<typename container, typename condition>
    auto FirstOrDefault(const container& c, condition&& cond) {
        auto res = std::find_first_if(std::begin(c),
                                      std::end(c),
                                      cond);
        return res == std::end(c)
                ? typename container::value_type()
                : *res;
    }

//GroupBy<TSource,TKey,TElement,TResult>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>, Func<TKey,IEnumerable<TElement>,TResult>)
//Groups the elements of a sequence according to a specified key selector function and creates a result value from each group and its key. The elements of each group are projected by using a specified function.
//GroupBy<TSource,TKey,TElement,TResult>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>, Func<TKey,IEnumerable<TElement>,TResult>, IEqualityComparer<TKey>)
//Groups the elements of a sequence according to a specified key selector function and creates a result value from each group and its key. Key values are compared by using a specified comparer, and the elements of each group are projected by using a specified function.
//GroupBy<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>)
//Groups the elements of a sequence according to a specified key selector function and projects the elements for each group by using a specified function.
//GroupBy<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>, IEqualityComparer<TKey>)
//Groups the elements of a sequence according to a key selector function. The keys are compared by using a comparer and each group's elements are projected by using a specified function.
//GroupBy<TSource,TKey,TResult>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TKey,IEnumerable<TSource>,TResult>)
//Groups the elements of a sequence according to a specified key selector function and creates a result value from each group and its key.
//GroupBy<TSource,TKey,TResult>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TKey,IEnumerable<TSource>,TResult>, IEqualityComparer<TKey>)
//Groups the elements of a sequence according to a specified key selector function and creates a result value from each group and its key. The keys are compared by using a specified comparer.
//GroupBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Groups the elements of a sequence according to a specified key selector function.
//GroupBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IEqualityComparer<TKey>)
//Groups the elements of a sequence according to a specified key selector function and compares the keys by using a specified comparer.
//GroupJoin<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,IEnumerable<TInner>,TResult>)
//Correlates the elements of two sequences based on equality of keys and groups the results. The default equality comparer is used to compare keys.
//GroupJoin<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,IEnumerable<TInner>,TResult>, IEqualityComparer<TKey>)
//Correlates the elements of two sequences based on key equality and groups the results. A specified IEqualityComparer<T> is used to compare keys.
//Intersect<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
//Produces the set intersection of two sequences by using the default equality comparer to compare values.
//Intersect<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
//Produces the set intersection of two sequences by using the specified IEqualityComparer<T> to compare values.
//Join<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,TInner,TResult>)
//Correlates the elements of two sequences based on matching keys. The default equality comparer is used to compare keys.
//Join<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,TInner,TResult>, IEqualityComparer<TKey>)
//Correlates the elements of two sequences based on matching keys. A specified IEqualityComparer<T> is used to compare keys.
//Last<TSource>(IEnumerable<TSource>)
//Returns the last element of a sequence.
//Last<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns the last element of a sequence that satisfies a specified condition.
//LastOrDefault<TSource>(IEnumerable<TSource>)
//Returns the last element of a sequence, or a default value if the sequence contains no elements.
//LastOrDefault<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns the last element of a sequence that satisfies a condition or a default value if no such element is found.
//LongCount<TSource>(IEnumerable<TSource>)
//Returns an Int64 that represents the total number of elements in a sequence.
//LongCount<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns an Int64 that represents how many elements in a sequence satisfy a condition.
//Max<TSource,TResult>(IEnumerable<TSource>, Func<TSource,TResult>)
//Invokes a transform function on each element of a generic sequence and returns the maximum resulting value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Decimal>)
//Invokes a transform function on each element of a sequence and returns the maximum Decimal value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Double>)
//Invokes a transform function on each element of a sequence and returns the maximum Double value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Int32>)
//Invokes a transform function on each element of a sequence and returns the maximum Int32 value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Int64>)
//Invokes a transform function on each element of a sequence and returns the maximum Int64 value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Decimal>>)
//Invokes a transform function on each element of a sequence and returns the maximum nullable Decimal value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Double>>)
//Invokes a transform function on each element of a sequence and returns the maximum nullable Double value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int32>>)
//Invokes a transform function on each element of a sequence and returns the maximum nullable Int32 value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int64>>)
//Invokes a transform function on each element of a sequence and returns the maximum nullable Int64 value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Single>>)
//Invokes a transform function on each element of a sequence and returns the maximum nullable Single value.
//Max<TSource>(IEnumerable<TSource>, Func<TSource,Single>)
//Invokes a transform function on each element of a sequence and returns the maximum Single value.
//Min(IEnumerable<Decimal>)
//Returns the minimum value in a sequence of Decimal values.
//Min(IEnumerable<Double>)
//Returns the minimum value in a sequence of Double values.
//Min(IEnumerable<Int32>)
//Returns the minimum value in a sequence of Int32 values.
//Min(IEnumerable<Int64>)
//Returns the minimum value in a sequence of Int64 values.
//Min(IEnumerable<Nullable<Decimal>>)
//Returns the minimum value in a sequence of nullable Decimal values.
//Min(IEnumerable<Nullable<Double>>)
//Returns the minimum value in a sequence of nullable Double values.
//Min(IEnumerable<Nullable<Int32>>)
//Returns the minimum value in a sequence of nullable Int32 values.
//Min(IEnumerable<Nullable<Int64>>)
//Returns the minimum value in a sequence of nullable Int64 values.
//Min(IEnumerable<Nullable<Single>>)
//Returns the minimum value in a sequence of nullable Single values.
//Min(IEnumerable<Single>)
//Returns the minimum value in a sequence of Single values.
//Min<TSource,TResult>(IEnumerable<TSource>, Func<TSource,TResult>)
//Invokes a transform function on each element of a generic sequence and returns the minimum resulting value.
//Min<TSource>(IEnumerable<TSource>)
//Returns the minimum value in a generic sequence.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Decimal>)
//Invokes a transform function on each element of a sequence and returns the minimum Decimal value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Double>)
//Invokes a transform function on each element of a sequence and returns the minimum Double value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Int32>)
//Invokes a transform function on each element of a sequence and returns the minimum Int32 value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Int64>)
//Invokes a transform function on each element of a sequence and returns the minimum Int64 value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Decimal>>)
//Invokes a transform function on each element of a sequence and returns the minimum nullable Decimal value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Double>>)
//Invokes a transform function on each element of a sequence and returns the minimum nullable Double value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int32>>)
//Invokes a transform function on each element of a sequence and returns the minimum nullable Int32 value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int64>>)
//Invokes a transform function on each element of a sequence and returns the minimum nullable Int64 value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Single>>)
//Invokes a transform function on each element of a sequence and returns the minimum nullable Single value.
//Min<TSource>(IEnumerable<TSource>, Func<TSource,Single>)
//Invokes a transform function on each element of a sequence and returns the minimum Single value.
//OfType<TResult>(IEnumerable)
//Filters the elements of an IEnumerable based on a specified type.
//OrderBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Sorts the elements of a sequence in ascending order according to a key.
//OrderBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Sorts the elements of a sequence in ascending order by using a specified comparer.
//OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Sorts the elements of a sequence in descending order according to a key.
//OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Sorts the elements of a sequence in descending order by using a specified comparer.
//Prepend<TSource>(IEnumerable<TSource>, TSource)
//Adds a value to the beginning of the sequence.
//Reverse<TSource>(IEnumerable<TSource>)
//Inverts the order of the elements in a sequence.
//SelectMany<TSource,TCollection,TResult>(IEnumerable<TSource>, Func<TSource,IEnumerable<TCollection>>, Func<TSource,TCollection,TResult>)
//Projects each element of a sequence to an IEnumerable<T>, flattens the resulting sequences into one sequence, and invokes a result selector function on each element therein.
//SelectMany<TSource,TCollection,TResult>(IEnumerable<TSource>, Func<TSource,Int32,IEnumerable<TCollection>>, Func<TSource,TCollection,TResult>)
//Projects each element of a sequence to an IEnumerable<T>, flattens the resulting sequences into one sequence, and invokes a result selector function on each element therein. The index of each source element is used in the intermediate projected form of that element.
//SelectMany<TSource,TResult>(IEnumerable<TSource>, Func<TSource,IEnumerable<TResult>>)
//Projects each element of a sequence to an IEnumerable<T> and flattens the resulting sequences into one sequence.
//SelectMany<TSource,TResult>(IEnumerable<TSource>, Func<TSource,Int32,IEnumerable<TResult>>)
//Projects each element of a sequence to an IEnumerable<T>, and flattens the resulting sequences into one sequence. The index of each source element is used in the projected form of that element.
//Single<TSource>(IEnumerable<TSource>)
//Returns the only element of a sequence, and throws an exception if there is not exactly one element in the sequence.
//Single<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns the only element of a sequence that satisfies a specified condition, and throws an exception if more than one such element exists.
//SingleOrDefault<TSource>(IEnumerable<TSource>)
//Returns the only element of a sequence, or a default value if the sequence is empty; this method throws an exception if there is more than one element in the sequence.
//SingleOrDefault<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns the only element of a sequence that satisfies a specified condition or a default value if no such element exists; this method throws an exception if more than one element satisfies the condition.
//Skip<TSource>(IEnumerable<TSource>, Int32)
//Bypasses a specified number of elements in a sequence and then returns the remaining elements.
//SkipWhile<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Bypasses elements in a sequence as long as a specified condition is true and then returns the remaining elements.
//SkipWhile<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
//Bypasses elements in a sequence as long as a specified condition is true and then returns the remaining elements. The element's index is used in the logic of the predicate function.
//Sum(IEnumerable<Decimal>)
//Computes the sum of a sequence of Decimal values.
//Sum(IEnumerable<Double>)
//Computes the sum of a sequence of Double values.
//Sum(IEnumerable<Int32>)
//Computes the sum of a sequence of Int32 values.
//Sum(IEnumerable<Int64>)
//Computes the sum of a sequence of Int64 values.
//Sum(IEnumerable<Nullable<Decimal>>)
//Computes the sum of a sequence of nullable Decimal values.
//Sum(IEnumerable<Nullable<Double>>)
//Computes the sum of a sequence of nullable Double values.
//Sum(IEnumerable<Nullable<Int32>>)
//Computes the sum of a sequence of nullable Int32 values.
//Sum(IEnumerable<Nullable<Int64>>)
//Computes the sum of a sequence of nullable Int64 values.
//Sum(IEnumerable<Nullable<Single>>)
//Computes the sum of a sequence of nullable Single values.
//Sum(IEnumerable<Single>)
//Computes the sum of a sequence of Single values.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Decimal>)
//Computes the sum of the sequence of Decimal values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Double>)
//Computes the sum of the sequence of Double values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Int32>)
//Computes the sum of the sequence of Int32 values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Int64>)
//Computes the sum of the sequence of Int64 values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Decimal>>)
//Computes the sum of the sequence of nullable Decimal values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Double>>)
//Computes the sum of the sequence of nullable Double values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int32>>)
//Computes the sum of the sequence of nullable Int32 values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Int64>>)
//Computes the sum of the sequence of nullable Int64 values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Nullable<Single>>)
//Computes the sum of the sequence of nullable Single values that are obtained by invoking a transform function on each element of the input sequence.
//Sum<TSource>(IEnumerable<TSource>, Func<TSource,Single>)
//Computes the sum of the sequence of Single values that are obtained by invoking a transform function on each element of the input sequence.
//TakeWhile<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Returns elements from a sequence as long as a specified condition is true.
//TakeWhile<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
//Returns elements from a sequence as long as a specified condition is true. The element's index is used in the logic of the predicate function.
//ThenBy<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>)
//Performs a subsequent ordering of the elements in a sequence in ascending order according to a key.
//ThenBy<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Performs a subsequent ordering of the elements in a sequence in ascending order by using a specified comparer.
//ThenByDescending<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>)
//Performs a subsequent ordering of the elements in a sequence in descending order, according to a key.
//ThenByDescending<TSource,TKey>(IOrderedEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Performs a subsequent ordering of the elements in a sequence in descending order by using a specified comparer.
//ToArray<TSource>(IEnumerable<TSource>)
//Creates an array from a IEnumerable<T>.
//ToDictionary<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>)
//Creates a Dictionary<TKey,TValue> from an IEnumerable<T> according to specified key selector and element selector functions.
//ToDictionary<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>, IEqualityComparer<TKey>)
//Creates a Dictionary<TKey,TValue> from an IEnumerable<T> according to a specified key selector function, a comparer, and an element selector function.
//ToDictionary<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Creates a Dictionary<TKey,TValue> from an IEnumerable<T> according to a specified key selector function.
//ToDictionary<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IEqualityComparer<TKey>)
//Creates a Dictionary<TKey,TValue> from an IEnumerable<T> according to a specified key selector function and key comparer.
//ToHashSet<TSource>(IEnumerable<TSource>)
//Creates a HashSet<T> from an IEnumerable<T>.
//ToHashSet<TSource>(IEnumerable<TSource>, IEqualityComparer<TSource>)
//Creates a HashSet<T> from an IEnumerable<T> using the comparer to compare keys.
//ToList<TSource>(IEnumerable<TSource>)
//Creates a List<T> from an IEnumerable<T>.
//ToLookup<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>)
//Creates a Lookup<TKey,TElement> from an IEnumerable<T> according to specified key selector and element selector functions.
//ToLookup<TSource,TKey,TElement>(IEnumerable<TSource>, Func<TSource,TKey>, Func<TSource,TElement>, IEqualityComparer<TKey>)
//Creates a Lookup<TKey,TElement> from an IEnumerable<T> according to a specified key selector function, a comparer and an element selector function.
//ToLookup<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Creates a Lookup<TKey,TElement> from an IEnumerable<T> according to a specified key selector function.
//ToLookup<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IEqualityComparer<TKey>)
//Creates a Lookup<TKey,TElement> from an IEnumerable<T> according to a specified key selector function and key comparer.
//Union<TSource>(IEnumerable<TSource>, IEnumerable<TSource>)
//Produces the set union of two sequences by using the default equality comparer.
//Union<TSource>(IEnumerable<TSource>, IEnumerable<TSource>, IEqualityComparer<TSource>)
//Produces the set union of two sequences by using a specified IEqualityComparer<T>.
//Where<TSource>(IEnumerable<TSource>, Func<TSource,Boolean>)
//Filters a sequence of values based on a predicate.
//Where<TSource>(IEnumerable<TSource>, Func<TSource,Int32,Boolean>)
//Filters a sequence of values based on a predicate. Each element's index is used in the logic of the predicate function.
//Zip<TFirst,TSecond,TResult>(IEnumerable<TFirst>, IEnumerable<TSecond>, Func<TFirst,TSecond,TResult>)
//Applies a specified function to the corresponding elements of two sequences, producing a sequence of the results.

// #include <algorithm>
// #include <numeric>

// namespace simlinq {

namespace detail
{
template <typename iter>
const auto &max(const iter &begin, const iter &end)
{
    if (begin == end)
        assert(false);
    return *std::max_element(begin, end);
}
} // namespace detail

/*
        Determines whether all elements of a sequence satisfy a condition.
     */
template <typename container, typename unary_predicate>
bool all(const container &src, unary_predicate &&condition)
{
    for (auto it = std::begin(src); it != std::end(src); ++it)
    {
        if (not condition(*it))
            return false;
    }
    return true;
}

/*
        Determines whether a sequence contains any elements.
     */
template <typename container>
bool any(const container &src)
{
    return std::begin(src) != std::end(src);
}

/*
        Determines whether any element of a sequence satisfies a condition.
     */
template <typename container, typename unary_predicate>
bool any(const container &src, unary_predicate &&condition)
{
    for (auto it = std::begin(src); it != std::end(src); ++it)
    {
        if (condition(*it))
            return true;
    }
    return false;
}

/*
        Concatenates two sequences.
    */
template <typename container>
auto concat(const container &first, const container &second)
{
    container result(std::size(first) + std::size(second));

    std::copy(std::begin(second),
              std::end(second),
              std::copy(std::begin(first),
                        std::end(first),
                        std::begin(result)));
    return result;
}

/*
        Determines whether any element of a sequence satisfies a condition.
     */
template <typename container, typename T>
bool contains(const container &src, const T &&value)
{
    return std::find(std::begin(src),
                     std::end(src),
                     value) != std::end(src);
}

/*
        Determines whether a sequence contains a specified element by using a specified binary predicate.
     */
template <typename container, typename T, typename binary_predicate>
bool contains(const container &src, const T &&value, binary_predicate &&predicate)
{
    for (auto it = std::begin(src); it != std::end(src); ++it)
    {
        if (predicate(*it, value))
            return true;
    }

    return false;
}

/*
        Returns the number of elements in a sequence.
     */
template <typename container>
auto count(const container &src)
{
    return std::distance(std::begin(src), std::end(src));
}

/*
        Returns a number that represents how many elements in the specified sequence satisfy a condition.
     */
template <typename container, typename unary_predicate>
auto count(const container &src, unary_predicate &&condition)
{
    return std::count_if(std::begin(src),
                         std::end(src),
                         condition);
}

/*
        Returns an empty IEnumerable<T> that has the specified type argument.
     */
template <typename T>
auto empty()
{
    return T{};
}

/*
        Produces the set difference of two sequences by using the default equality comparer to compare values.
     */
template <typename container>
auto except(const container &first, const container &second)
{
    container result;
    std::copy_if(std::begin(first),
                 std::end(first),
                 std::back_inserter(result),
                 [&second](const typename container::value_type &value) {
                     return std::find(std::begin(second), std::end(second), value) == std::end(second);
                 });
    return result;
}

/*
        Produces the set difference of two sequences by using the specified IEqualityComparer<T> to compare values.
     */
template <typename container, typename binary_predicate>
auto except(const container &first, const container &second, binary_predicate &&comparator)
{
    container result;
    std::copy_if(std::begin(first),
                 std::end(first),
                 std::back_inserter(result),
                 [&second, &comparator](const typename container::value_type &value) {
                     return std::find_if(std::begin(second),
                                         std::end(second),
                                         [&comparator, &value](const typename container::value_type &nested_value) {
                                             return comparator(value, nested_value);
                                         }) == std::end(second);
                 });
    return result;
}

/*
        Returns the maximum value in a sequence.
     */
template <typename container>
const auto &max(const container &src)
{
    return detail::max(std::begin(src),
                       std::end(src));
}

/*
        Projects each element of a sequence into a new form by incorporating the element's index.
     */
template <template <typename, typename> class ret_type, typename container, typename ind_type = uint32_t>
auto select(container &src)
{
    using pair = std::pair<ind_type, typename container::value_type>;
    ret_type<pair, std::allocator<pair>> result(src.size());

    for (ind_type i = 0; i < std::size(src); ++i)
    {
        result[i] = pair{i, src[i]};
    }
    return result;
}

/*
        Projects each element of a sequence into a new form.
     */
template <template <typename, typename> class ret_type, typename container, typename transform_func>
auto select(container &src, transform_func &&f)
{
    ret_type<typename container::value_type, std::allocator<typename container::value_type>> result(src);

    std::transform(std::begin(src), std::end(src), result.begin(), f);

    return result;
}

/*
        Determines whether two sequences are equal by comparing the elements by using the default equality comparer for their type.
     */
template <typename container>
bool sequenceEqual(const container &first, const container &second)
{
    return std::size(first) == std::size(second)
               ? std::equal(std::begin(first), std::end(first), std::begin(second))
               : false;
}

/*
        Determines whether two sequences are equal by comparing their elements by using a specified IEqualityComparer<T>
     */
template <typename container, typename comparator>
bool sequenceEqual(const container &first, const container &second, comparator &&comp)
{
    return std::size(first) == std::size(second)
               ? std::equal(std::begin(first), std::end(first), std::begin(second), comp)
               : false;
}

/*
        Generates a sequence of integral numbers within a specified range.
     */
template <typename container, typename T>
auto range(T &&value, uint32_t count)
{
    container c(count);
    std::iota(std::begin(c), std::end(c), value);
    return c;
}

/*
        Generates a sequence that contains one repeated value.
     */
template <typename container, typename T>
container repeat(T &&value, uint32_t count)
{
    return container(count, value);
}

/*
        Returns a specified number of contiguous elements from the start of a sequence.
     */
template <unsigned int N, typename container>
container take(const container &src)
{
    if (std::begin(src) + N >= std::end(src))
        return src;

    container result(N);
    std::copy(std::begin(src), std::begin(src) + N, std::begin(result));
    return result;
}
} // namespace simlinq
