#include <algorithm>
#include <numeric>
#include <optional>
#include <unordered_set>
#include <vector>
#include <string>

namespace simlinq {

    
    namespace detail {
        
        template<typename container>
        bool is_sorted(const container& c) {
            return std::is_sorted(std::begin(c), std::end(c));
        }
        
        template<typename container, typename binary_predicate>
        bool is_sorted(const container& c, binary_predicate&& comparer) {
            return std::is_sorted(std::begin(c), std::end(c), comparer);
        }
        
        template<typename container>
        auto copy_sort(container src) {
            std::sort(std::begin(src), std::end(src));
            return src;
        }
        
        template<typename container, typename binary_predicate>
        auto copy_sort(container src, binary_predicate&& comparer) {
            std::sort(std::begin(src), std::end(src), comparer);
            return src;
        }
        
        template<typename container>
        inline auto distinct_impl(const container& f, const container& s) {
            container r;
            std::set_difference(std::begin(f), std::end(f),
                                std::begin(s), std::end(s),
                                std::back_inserter(r));
            return r;
        }
        
        template<typename container, typename binary_predicate>
        inline auto distinct_impl(const container& f, const container& s, binary_predicate&& comparer) {
            container r;
            std::set_difference(std::begin(f), std::end(f),
                                std::begin(s), std::end(s),
                                std::back_inserter(r),
                                comparer);
            return r;
        }

    }
    
    

    /*
        Applies an accumulator function over a sequence. The specified seed value is used as the initial accumulator value, and the specified function is used to select the result value.
    */
    template<typename container, typename seed, typename accumulator, typename selector>
    auto Aggregate(const container& src, seed&& s, accumulator&& acc, selector&& sel) {
        decltype(acc) result(s);

        for (const auto& value : src) {
            acc(value, result);
        }
        return sel(result);
    }


    /*
        Applies an accumulator function over a sequence. The specified seed value is used as the initial accumulator value.
    */
    template<typename container, typename seed, typename accumulator>
    auto Aggregate(const container& src, seed&& s, accumulator&& acc) {
        decltype(acc) result(s);

        for (const auto& value : src) {
            acc(value, result);
        }
        result;
    }


    /*
        Applies an accumulator function over a sequence.
    */
    template <typename container, typename accumulator>
    auto Aggregate(const container &c, accumulator &&acc) {
        typename container::value_type result;

        for (const auto &value : c)
        {
            acc(value, result);
        }

        return result;
    }


    /*
        Appends a value to the end of the sequence.
    */
    template <typename container>
    void Append(container &c, typename container::value_type &value) {
        // TODO: this is bad container-specific implementation; should be rewritten.
        c.push_back(value);
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


    /*
        Computes the average of a sequence that are obtained by invoking a transform function on each element of the input sequence.
    */
    template <typename container, typename transform>
    auto Average(const container &src, transform &&trans) {
        using optional_type = std::optional<decltype(trans)>;

        if (std::begin(src) == std::end(src)) {
            return optional_type();
        }

        decltype(trans) result;
        for (const auto &value : src)
        {
            result += trans(src);
        }
        result /= std::size(src);
        return optional_type(result);
    }


    /*
        Casts the elements of an IEnumerable to the specified type.
    */
    template<typename cast_type, typename container> 
    auto Cast(const container& src) {
        std::vector<cast_type> result;

        std::transform(std::begin(src),
                       std::end(src),
                       std::begin(result),
                       [](const auto& value) { return static_cast<cast_type>(value); }
                       );
        return result;
    }

    
    /*
        Returns the elements of the specified sequence or the type parameter's default value in a singleton collection if the sequence is empty.
     */
    template<typename container>
    auto DefaultIfEmpty(const container& src) {
        return std::size(src) != 0
            ? src
            : container({ typename container::value_type{} });
    }
    
    
    /*
        Returns the elements of the specified sequence or the specified value in a singleton collection if the sequence is empty.
     */
    template<typename container>
    auto DefaultIfEmpty(const container& src, typename container::value_type value) {
        return std::size(src) != 0
            ? src
            : container({ value });
    }

    
    /*
        Returns distinct elements from a sequence by using the default equality comparer to compare values.
     */
    template<typename container>
    auto Distinct(const container& first, const container& second) {
        using namespace detail;
        
        if (is_sorted(first) and is_sorted(second)) {
            return distinct_impl(first, second);
        }
        
        return distinct_impl( copy_sort(first),
                              copy_sort(second));
    }
    
    
    /*
        Returns distinct elements from a sequence by using a specified IEqualityComparer<T> to compare values.
     */
    template<typename container, typename binary_predicate>
    auto Distinct(const container& first, const container& second, binary_predicate&& comparer) {
        using namespace detail;
        
        if (is_sorted(first, comparer) and is_sorted(second, comparer)) {
            return distinct_impl(first, second, comparer);
        }
        
        return distinct_impl( copy_sort(first, comparer),
                              copy_sort(second, comparer),
                              comparer);
    }
    
    
    /*
        Returns the element at a specified index in a sequence.
     */
    template<typename container>
    auto ElementAt(const container& src, int index) {
        using optional_type = std::optional<typename container::value_type>;
        
        return (index < std::size(src) and index >= 0)
            ? optional_type(*(std::begin(src) + index))
            : optional_type();
    }
    
    
    /*
        Returns the element at a specified index in a sequence or a default value if the index is out of range.
     */
    template<typename container>
    auto ElementAtOrDefault(const container& src, int index) {
        return (index < std::size(src) and index >= 0)
            ? *(std::begin(src) + index)
            : typename container::value_type();
    }
    
    
    /*
        Returns the first element of a sequence.
    */
    template <typename container>
    auto First(const container &src) {
        using optional_type = std::optional<typename container::value_type>;
        
        return std::begin(src) == std::end(src)
            ? optional_type()
            : optional_type(src.front());
    }


    /*
        Returns the first element in a sequence that satisfies a specified condition.
    */
    template<typename container, typename unary_predicate>
    auto First(const container& c, unary_predicate&& condition) {
        using optional_type = std::optional<typename container::value_type>;

        auto res = std::find_if(std::begin(c),
                                std::end(c),
                                condition);
        return res == std::end(c)
                ? optional_type()
                : optional_type(*res);
    }


    /*
        Returns the first element of a sequence, or a default value if the sequence contains no elements.
    */
    template<typename container>
    auto FirstOrDefault(const container& c) {
        return std::begin(c) == std::end(c)
            ? typename container::value_type()
            : typename container::value_type(c.front());
    }


    /*
        Returns the first element of the sequence that satisfies a condition or a default value if no such element is found.
    */
    template<typename container, typename condition>
    auto FirstOrDefault(const container& c, condition&& cond) {
        auto res = std::find_if(std::begin(c),
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
    
    /*
        Produces the set intersection of two sequences by using the default equality comparer to compare values.
     */
    template<typename container>
    auto Intersect(const container& first, const container& second) {
        auto prepare = [](auto src) {
             std::sort(std::begin(src), std::end(src));
            return src;
        };

        container first_c = prepare(first);
        container second_c = prepare(second);
        
        container result;
        std::set_intersection(std::begin(first_c), std::end(first_c),
                              std::begin(second_c), std::end(second_c),
                              std::back_inserter(result));
        return result;
    }
    
    
    /*
        Produces the set intersection of two sequences by using the specified IEqualityComparer<T> to compare values.
     */
    template<typename container, typename comparator>
    auto Intersect(const container& first, const container& second, comparator&& comp) {
        auto prepare = [&comp](auto src) {
            std::sort(std::begin(src), std::end(src), comp);
            return src;
        };

        container first_c = prepare(first);
        container second_c = prepare(second);
        
        container result;
        std::set_intersection(std::begin(first_c), std::end(first_c),
                              std::begin(second_c), std::end(second_c),
                              std::back_inserter(result),
                              comp);
        return result;
    }
    
//Join<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,TInner,TResult>)
//Correlates the elements of two sequences based on matching keys. The default equality comparer is used to compare keys.
//Join<TOuter,TInner,TKey,TResult>(IEnumerable<TOuter>, IEnumerable<TInner>, Func<TOuter,TKey>, Func<TInner,TKey>, Func<TOuter,TInner,TResult>, IEqualityComparer<TKey>)
//Correlates the elements of two sequences based on matching keys. A specified IEqualityComparer<T> is used to compare keys.

    /*
        Returns the last element of a sequence.
    */
    template <typename container>
    auto Last(const container &src) {
        using optional_type = std::optional<typename container::value_type>;

        return std::begin(src) == std::end(src)
            ? optional_type()
            : optional_type(src.back());
    }


    /*
        Returns the last element of a sequence that satisfies a specified condition.
    */
    template<typename container, typename unary_predicate>
    auto Last(const container& c, unary_predicate&& cond) {
        using optional_type = std::optional<typename container::value_type>;

        auto res = std::find_if(std::rbegin(c),
                                std::rend(c),
                                cond);
        return res == std::rend(c)
                ? optional_type()
                : optional_type(*res);
    }


    /* 
        Returns the last element of a sequence, or a default value if the sequence contains no elements.
    */
    template<typename container>
    auto LastOrDefault(const container& c) {
        return std::begin(c) == std::end(c)
            ? typename container::value_type()
            : typename container::value_type(c.back());
    }


    /*
        Returns the last element of a sequence that satisfies a condition or a default value if no such element is found.
    */
    template<typename container, typename condition>
    auto LastOrDefault(const container& c, condition&& cond) {
        auto res = std::find_if(std::rbegin(c),
                                std::rend(c),
                                cond);
        return res == std::rend(c)
                ? typename container::value_type()
                : *res;
    }


    /*
        Returns an Int64 that represents the total number of elements in a sequence.
     */
    template <typename container>
    long long LongCount(const container &src) {
        return static_cast<long long>( std::size(src) );
    }

    /*
        Returns an Int64 that represents how many elements in a sequence satisfy a condition.
     */
    template <typename container, typename unary_predicate>
    long long LongCount(const container &src, unary_predicate &&condition) {
        return static_cast<long long>(std::count_if(std::begin(src),
                                                    std::end(src),
                                                    condition));
    }

        
    /*
        Returns the maximum value in a sequence.
    */
    template <typename container>
    auto Max(const container &src) {
        using optional_type = std::optional<typename container::value_type>;
        
        return std::begin(src) == std::end(src)
            ? optional_type()
            : optional_type(*(std::max_element(std::begin(src), std::end(src))));
    }
    
    
    /*
        Invokes a transform function on each element of a generic sequence and returns the maximum resulting value.
    */
    template<typename container, typename transform>
    auto Max(const container& c, transform&& trans) {
        using optional_type = std::optional<typename container::value_type>;

        if (std::begin(c) == std::end(c)) {
            return optional_type();
        }
        
        auto max_value = trans(*std::begin(c));
        for (const auto& value : c) {
            max_value = std::max(trans(value), max_value);
        } 
        return optional_type(max_value);
    }
    

    /*
        Returns the minimum value in a sequence.
    */
    template<typename container>
    auto Min(const container& c) {
        using optional_type = std::optional<typename container::value_type>;

        return std::begin(c) == std::end(c)
            ? optional_type()
            : optional_type(*(std::min_element(std::begin(c), std::end(c))));
    }


    /*
        Invokes a transform function on each element of a generic sequence and returns the minimum resulting value.
    */
    template<typename container, typename transform>
    auto Min(const container& c, transform&& trans) {
        using optional_type = std::optional<typename container::value_type>;

        if (std::begin(c) == std::end(c))
            return optional_type();
        
        auto min_value = trans(*std::begin(c));
        for (const auto& value : c) {
            min_value = std::min(trans(value), min_value);
        } 
        return optional_type(min_value);
    }

    
    /*
        Filters the elements of an IEnumerable based on a specified type.
     */
    template<typename required_type, typename container>
    auto OfType(const container& src) {
        container result;
        
    std::copy_if(std::begin(src),
                 std::end(src),
                 std::back_inserter(result),
                 [](auto& v) { return dynamic_cast<required_type>(v) != nullptr; }
                 );
        return result;
    }
    
    
//OrderBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Sorts the elements of a sequence in ascending order according to a key.
//OrderBy<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Sorts the elements of a sequence in ascending order by using a specified comparer.
//OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>)
//Sorts the elements of a sequence in descending order according to a key.
//OrderByDescending<TSource,TKey>(IEnumerable<TSource>, Func<TSource,TKey>, IComparer<TKey>)
//Sorts the elements of a sequence in descending order by using a specified comparer.

    /*
        Adds a value to the beginning of the sequence.
    */
    template<typename container>
    void Prepend(const container& src, typename container::value_type&& value) {
        src.insert(std::begin(src),
                   value);
    }


    /*
        Inverts the order of the elements in a sequence.
    */
    template<typename container>
    void Reverse(container& src) {
        std::reverse( std::begin(src), std::end(src) );
    }

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

    /*
        Computes the sum of a sequence of Decimal values.
    */
    template<typename container>
    auto Sum(const container& c) {
        return std::accumulate(std::begin(c), 
                               std::end(c),
                               typename container::value_type());
        
    }


    /*
        Computes the sum of the sequence of Decimal values that are obtained by invoking a transform function on each element of the input sequence.
    */
    template<typename container, typename transform>        
    auto Sum(const container& c, transform&& trans) {
        return std::accumulate(std::begin(c),
                               std::end(c),
                               typename container::value_type(),
                               trans);
    }


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

    /*
        Produces the set union of two sequences by using the default equality comparer.
    */
    template<typename container>
    auto Union(const container& first, const container& second) {
        std::unordered_set<typename container::value_type> result(std::begin(first), std::end(first));

        std::copy(std::begin(second), 
                  std::end(second),
                  std::inserter(result, std::end(result))
                  );
        return result;
    }


    /*
        Produces the set union of two sequences by using a specified IEqualityComparer<T>.
    */
    template<typename container, typename comparator>
    auto Union(const container& first, const container& second, comparator&& comp) {
        using value_type = typename container::value_type;
        std::unordered_set<value_type, std::hash<value_type>, decltype(comp)> result(std::begin(first), std::end(second));

        std::copy(std::begin(second), 
                  std::end(second),
                  std::inserter(result, std::end(result))
                  );
        return result;
    }


    /*
        Filters a sequence of values based on a predicate.
    */
    template<typename container, typename unary_predicate>
    auto Where(const container& src, unary_predicate&& predicate) {
        container result;

        std::copy_if(std::begin(src),
                     std::end(src),
                     std::back_inserter(result),
                     predicate);
        return result;
    }


    /*
        Filters a sequence of values based on a predicate. Each element's index is used in the logic of the predicate function.
    */
//    template<typename container, typename binary_predicate>
//    auto Where(const container& src, binary_predicate&& predicate) {
//        container result;
//        size_t index = 0;
//        for (const auto& value : src) {
//            if (predicate(index, value)) {
//                result.push_back(value);
//            }
//            index ++;
//        }
//
//        return result;
//    }



    /*
        Applies a specified function to the corresponding elements of two sequences, producing a sequence of the results.
     */
    template<typename first_container,
             typename second_container,
             typename binary_predicate>
    auto Zip(const first_container& first, const second_container& second, binary_predicate&& predicate) {
        /*
            TODO: Further investigations required
         */
        std::vector<std::string> result;
        
        auto count = std::min(std::size(first), std::size(second));
        
        auto fit = std::begin(first);
        auto sit = std::begin(second);
        for (;
             fit < std::begin(first) + count;
             ++fit, ++sit) {
            result.push_back( predicate(*fit, *sit));
        }
        
        return result;
    }

    /*
        Determines whether all elements of a sequence satisfy a condition.
     */
    template <typename container, typename unary_predicate>
    bool All(const container &src, unary_predicate &&condition) {
        return std::all_of(std::begin(src),
                           std::end(src),
                           condition);
    }

    /*
        Determines whether a sequence contains any elements.
     */
    template <typename container>
    bool Any(const container &src) {
        return std::begin(src) != std::end(src);
    }

    /*
        Determines whether any element of a sequence satisfies a condition.
    */
    template <typename container, typename unary_predicate>
    bool Any(const container &src, unary_predicate &&condition) {
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
    auto Concat(const container &first, const container &second) {
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
    bool Contains(const container &src, const T &&value) {
        return std::find(std::begin(src),
                        std::end(src),
                        value) != std::end(src);
    }

    /*
        Determines whether a sequence contains a specified element by using a specified binary predicate.
    */
    template <typename container, typename T, typename binary_predicate>
    bool Contains(const container &src, const T &&value, binary_predicate &&predicate) {
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
    auto Count(const container &src) {
        return std::size(src);
    }

    /*
        Returns a number that represents how many elements in the specified sequence satisfy a condition.
    */
    template <typename container, typename unary_predicate>
    auto Count(const container &src, unary_predicate &&condition) {
        return std::count_if(std::begin(src),
                            std::end(src),
                            condition);
    }

    /*
        Returns an empty IEnumerable<T> that has the specified type argument.
    */
    template <typename T>
    auto Empty() {
        return T{};
    }

    /*
        Produces the set difference of two sequences by using the default equality comparer to compare values.
    */
    template <typename container>
    auto except(const container &first, const container &second) {
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
    auto except(const container &first, const container &second, binary_predicate &&comparator) {
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
        Projects each element of a sequence into a new form by incorporating the element's index.
    */
    template <template <typename, typename> class ret_type, typename container, typename ind_type = uint32_t>
    auto select(container &src) {
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
    auto select(container &src, transform_func &&f) {
        ret_type<typename container::value_type, std::allocator<typename container::value_type>> result(src);

        std::transform(std::begin(src), std::end(src), result.begin(), f);

        return result;
    }

    /*
        Determines whether two sequences are equal by comparing the elements by using the default equality comparer for their type.
    */
    template <typename container>
    bool SequenceEqual(const container &first, const container &second) {
        return std::size(first) == std::size(second)
                ? std::equal(std::begin(first), std::end(first), std::begin(second))
                : false;
    }

    /*
        Determines whether two sequences are equal by comparing their elements by using a specified IEqualityComparer<T>
    */
    template <typename container, typename comparator>
    bool SequenceEqual(const container &first, const container &second, comparator &&comp) {
        return std::size(first) == std::size(second)
                ? std::equal(std::begin(first), std::end(first), std::begin(second), comp)
                : false;
    }

    /*
        Generates a sequence of integral numbers within a specified range.
    */
    template <typename container, typename T>
    auto range(T &&value, uint32_t count) {
        container c(count);
        std::iota(std::begin(c), std::end(c), value);
        return c;
    }

    /*
        Generates a sequence that contains one repeated value.
    */
    template <typename container, typename T>
    container Repeat(T &&value, uint32_t count) {
        return container(count, value);
    }

    /*
        Returns a specified number of contiguous elements from the start of a sequence.
    */
    template <unsigned int N, typename container>
    container Take(const container &src) {
        if (std::begin(src) + N >= std::end(src))
            return src;

        container result(N);
        std::copy(std::begin(src), std::begin(src) + N, std::begin(result));
        return result;
    }

} // namespace simlinq
