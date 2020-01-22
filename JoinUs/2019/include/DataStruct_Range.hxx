inline int Range::first(int lowRange) const
{ 
	if ( first_ == fromStart ) return lowRange;
	return first_; 
}

inline int Range::last(int highRange) const
{
	if ( last_ == toEnd ) return highRange;
	return last_;
}

inline unsigned Range::length( int ) const
{
	return ( last_ - first_ ) / stride_ + 1;
}

inline int Range::stride() const
{
	return stride_;
}

inline bool Range::isAscendingContiguous() const
{
	return ( ( first_ < last_ ) && (stride_ == 1) || (first_ == last_) );
}

inline void Range::setRange(int first, int last, int stride)
{
	first_ = first;
	last_ = last;
	stride_ = stride;
}

inline bool Range::isUnitStride() const
{ 
	return stride_ == 1;
}

inline bool Range::hasFastAccess() const
{ 
	return stride_ == 1;
}

inline Range::T_numtype Range::fastAccess(unsigned i) const
{
	return first_ + i; 
}

inline unsigned Range::suggestLength() const
{ 
	return length();
}