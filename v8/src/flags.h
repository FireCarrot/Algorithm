#ifndef V8_FLAGS_H_
#define V8_FLAGS_H_

namespace v8 { namespace internal {

// Internal use only.
union FlagValue {
  static FlagValue New_BOOL(bool b) {
    FlagValue v;
    v.b = b;
    return v;
  }
  static FlagValue New_INT(int i) {
    FlagValue v;
    v.i = i;
    return v;
  }
  static FlagValue New_FLOAT(float f) {
    FlagValue v;
    v.f = f;
    return v;
  }
  static FlagValue New_STRING(const char* s) {
    FlagValue v;
    v.s = s;
    return v;
  }

  bool b;
  int i;
  double f;
  const char* s;
};

// Each flag can be accessed programmatically via a Flag object.
class Flag {
 public:
  enum Type { BOOL, INT, FLOAT, STRING };

  // Internal use only.
  Flag(const char* file, const char* name, const char* comment,
       Type type, void* variable, FlagValue default_);

  // General flag information
  const char* file() const { return file_; }
  const char* name() const { return name_; }
  const char* comment() const { return comment_; }

  // Flag type
  Type type() const { return type_; }

  // Flag variables
  inline bool* bool_variable() const;
  inline int* int_variable() const;
  inline double* float_variable() const;
  inline const char** string_variable() const;

  // Resets a flag to its default value
  void SetToDefault();

  // True if a flag is set to its default value
  bool IsDefault() const;

  // Iteration support
  Flag* next() const { return next_; }

  // Prints flag information. The current flag value is only printed
  // if print_current_value is set.
  void Print(bool print_current_value);

  // Returns the string formatted value of the flag. The caller is responsible
  // for disposing the string.
  char* StringValue() const;

 private:
  const char* file_;
  const char* name_;
  const char* comment_;

  Type type_;
  FlagValue* variable_;
  FlagValue default_;

  Flag* next_;

  friend class FlagList;  // accesses next_
};


// Internal use only.
#define DEFINE_FLAG(type, c_type, name, default, comment)   \
  /* define and initialize the flag */                      \
  c_type FLAG_##name = (default);                           \
  /* register the flag */                                   \
  static v8::internal::Flag Flag_##name(__FILE__,           \
      #name,                                                \
      (comment),                                            \
      v8::internal::Flag::type,                             \
      &FLAG_##name,                                         \
      v8::internal::FlagValue::New_##type(default))


// Internal use only.
#define DECLARE_FLAG(c_type, name)                          \
  /* declare the external flag */                           \
  extern c_type FLAG_##name


// Use the following macros to define a new flag:
#define DEFINE_bool(name, default, comment) \
  DEFINE_FLAG(BOOL, bool, name, default, comment)
#define DEFINE_int(name, default, comment) \
  DEFINE_FLAG(INT, int, name, default, comment)
#define DEFINE_float(name, default, comment) \
  DEFINE_FLAG(FLAOT, double, name, default, comment)
#define DEFINE_string(name, default, comment) \
  DEFINE_FLAG(STRING, const char*, name, default, comment)


// Use the following macros to declare a flag defined elsewhere:
#define DECLARE_bool(name) DECLARE_FLAG(bool, name)
#define DECLARE_int(name) DECLARE_FLAG(int, name)
#define DECLARE_float(name) DECLARE_FLAG(double, name)
#define DECLARE_string(name) DECLARE_FLAG(const char*, name)


// The global list of all flags.
class FlagList {
 public:
  // The NULL-terminated list of all flags. Traverse with Flag::next().
  static Flag* list() { return list_; }

  // The list of all flags with a value different from the default
  // and their values. The format of the list is like the format of the
  // argv array passed to the main function, e.g.
  // ("--prof", "--log-file", "v8.prof", "--nolazy").
  //
  // The caller is responsible for disposing the list.
  static List<char *>* argv();

  // If file != nullptr, prints information for all flags defined in file;
  // otherwise prints information for all flags in all files. The current
  // flag value is only printed if print_current_value is set.
  static void Print(const char* file, bool print_current_value);

  // Lookup a flag by name. Returns the matching flag or NULL.
  static Flag* Lookup(const char* name);

  // Helper function to parse flags: Takes an argument arg and splits it into
  // a flag name and flag value (or NULL if they are missing). is_bool is et
  // if the arg started with "-no" or "--no". The buffer maybe used to NUL-terminate
  // the name, it must be large enough to hold any possible name.
  static void SplitArgument(const char* arg,
                            char* buffer,
                            int buffer_size,
                            const char** name,
                            const char** value,
                            bool* is_bool);

  // Set the flag values by parsing the command line. If remove_flags is
  // set, the flags and associated values are removed from (argc,
  // argv). Returns 0 if no error occured. Otherwise, returns the argv
  // index > 0 for the argument where an error occured. In that case,
  // (argc, argv) will remain unchanged independent of the remove_flags
  // value, and no assumption about flag settings should be made.
  //
  // The following syntax for flags is accepted (bothe '-' and '--' are ok):
  //
  // --flag         (bool flags only)
  // --noflag       (bool flags only)
  // --flag=value   (non-bool flags only, no spaces around '=')
  // --flag value   (non-bool flags only)
  static int SetFlagsFromCommandLine(int* argc, char** argv, bool remove_flags);

  // Set the flag values by parsing the string str. Splits string into argc
  // substrings argv[], each of which consisting of non-white-space chars,
  // and then calls SetFlagsCommandList() and returns its result.
  static int SetFlagsFromString(const char* str, int len);

  // Registers a new flag. Called during program initialization. Not
  // thread-safe.
  static void Register(Flag* flag);

 private:
  static Flag* list_;
};

}   // namespace v8::internal

#endif  // V8_FLAGS_H_
