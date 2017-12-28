
template<typename T> //iterate over all subsets of size k
void iterate_k_subsets(vector<T>& data, int k, function<void(vector<T>&)> lambda)
{
    assert(data.size() >= k);
    auto inside = vector<bool>(data.size(), false);
    fill(inside.begin(), inside.begin()+k, true);
    auto subset = vector<T>;
    subset.reserve(k);
    do
    {
        subset.clear();
        for(int i=0; i<inside.size(), ++i)
            if(inside[i])
                subset.push_back[data[i]];
        lambda(subset);
    }
    while(prev_permutation(inside.begin(), inside.end()));
}
