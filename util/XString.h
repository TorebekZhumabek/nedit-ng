
#ifndef XSTRING_H_
#define XSTRING_H_

#include <memory>
#include <algorithm>
#include <cassert>
#include <Xm/Xm.h>
#include "MotifHelper.h"

// NOTE(eteran): this does more copies than necessary, we could do reference
//               counting, but we would rather this be "obviously" correct

class XString {
public:
	typedef char*       iterator;
	typedef const char* const_iterator;
	
public:
	XString() : ptr_(nullptr), size_(0) {
	}
	
	explicit XString(nullptr_t) : ptr_(nullptr), size_(0) {
	}
	
	explicit XString(const std::string &text) : ptr_(nullptr), size_(0) {
	
	
		size_ = text.size();	
		
		ptr_  = XtMalloc(size_ + 1);
		strncpy(ptr_, text.c_str(), size_ + 1);
		ptr_[size_] = '\0';
			
	}
	
	explicit XString(const char *text) : ptr_(nullptr), size_(0) {
		if(text) {
			size_ = strlen(text);
			ptr_  = XtMalloc(size_ + 1);
			strcpy(ptr_, text);
		}
	}	
	
	XString(const char *text, size_t length) : ptr_(nullptr), size_(length) {
		if(text) {	
			size_ = length;	
			ptr_  = XtMalloc(size_ + 1);
			strncpy(ptr_, text, size_ + 1);
			ptr_[size_] = '\0';
		}
	}
	
	XString(const XString &other) : ptr_(nullptr), size_(0) {
		if(other.ptr_) {	
			size_ = strlen(other.ptr_);
			ptr_  = XtMalloc(size_ + 1);
			strcpy(ptr_, other.ptr_);
		}	
	}
	
	XString& operator=(const XString &rhs) {
		if(this != &rhs) {
			XString(rhs).swap(*this);
		}
		return *this;
	}
	
	XString& operator=(const std::string &rhs) {
		XString(rhs).swap(*this);
		return *this;
	}	
	
	XString(XString &&other) : ptr_(other.ptr_), size_(other.size_) {
		other.ptr_  = nullptr;
		other.size_ = 0;
	}
	
	XString& operator=(XString &&rhs) {
		if(this != &rhs) {
			XString(std::move(rhs)).swap(*this);
		}
		return *this;
	}

	~XString() {
		XtFree(ptr_);
	}

public:
	size_t size() const {
		return size_;
	}
	
	bool empty() const {
		return size_ == 0;
	}
	
	explicit operator bool() const {
		return ptr_ != nullptr;
	}
	
public:
	iterator begin()             { return ptr_;          }
	iterator end()               { return ptr_ + size_; }
	const_iterator begin() const { return ptr_;          }
	const_iterator end() const   { return ptr_ + size_; }
	
public:
	char operator[](size_t index) const {
		return ptr_[index];
	}
	
	char& operator[](size_t index) {
		return ptr_[index];
	}
	
	char *c_str() {
		return ptr_;
	}
	
	const char *c_str() const {
		return ptr_;
	}
	
	char *data() {
		return ptr_;
	}
	
	const char *data() const {
		return ptr_;
	}	

public:
	int compare(const char *s) const {
		assert(s);
		return strcmp(ptr_, s);
	}
	
	int compare(const std::string &s) const {
		return strcmp(ptr_, s.c_str());
	}	
	
	int compare(const XString &s) const {
		return strcmp(ptr_, s.ptr_);
	}	
	
public:
	XmString toXmString() const {
		return XmStringCreateSimple(ptr_);
	}
	
public:
	// NOTE(eteran): takes ownership of the string instead of copying it
	// and thus will free it later
	static XString takeString(char *s) {
		XString str;
		str.ptr_  = s;
		str.size_ = strlen(s);
		return str;
	}
	
	template <class... Args>
	static XString format(const char *format, Args... args) {
	
		int length = snprintf(nullptr, 0, format, args...);	
		char *s    = XtMalloc(length + 1);
		snprintf(s, length + 1, format, args...);	
		
		XString str;
		str.ptr_  = s;
		str.size_ = length;
		return str;
	}
	
public:
	void swap(XString &other) {
		using std::swap;
		swap(ptr_,  other.ptr_);
		swap(size_, other.size_);
	}
	
private:
	char  *ptr_;
	size_t size_;
};

inline bool operator==(const XString &lhs, const XString &rhs) {
	return lhs.compare(rhs) == 0;
}

inline bool operator!=(const XString &lhs, const XString &rhs) {
	return lhs.compare(rhs) != 0;
}

inline bool operator==(const char *lhs, const XString &rhs) {
	assert(lhs);
	return rhs.compare(lhs) == 0;
}

inline bool operator!=(const char *lhs, const XString &rhs) {
	assert(lhs);
	return rhs.compare(lhs) != 0;
}

inline bool operator==(const XString &lhs, const char *rhs) {
	assert(rhs);
	return lhs.compare(rhs) == 0;
}

inline bool operator!=(const XString &lhs, const char *rhs) {
	assert(rhs);
	return lhs.compare(rhs) != 0;
}

inline bool operator==(const std::string &lhs, const XString &rhs) {
	return rhs.compare(lhs) == 0;
}

inline bool operator!=(const std::string &lhs, const XString &rhs) {
	return rhs.compare(lhs) != 0;
}

inline bool operator==(const XString &lhs, const std::string &rhs) {
	return lhs.compare(rhs) == 0;
}

inline bool operator!=(const XString &lhs, const std::string &rhs) {
	return lhs.compare(rhs) != 0;
}


// try to cause a linker error if we use a null pointer
bool operator==(nullptr_t, const XString &rhs);
bool operator!=(nullptr_t, const XString &rhs);
bool operator==(const XString &lhs, nullptr_t);
bool operator!=(const XString &lhs, nullptr_t);

#endif