#include <ctype.h>
#include <stdlib.h>

#include "v8.h"

#include "platform.h"

namespace v8 { namespace internal {

// Helpers

static inline char NormalizeChar(char ch) {
  return ch == '_' ? '-' : ch;
}


static const char* NormalizeName(const char* name) {
  int len = strlen(name);
  char* result = NewArray<char>(len+1);
  for (int i = 0; i <= len; i++) {
    result[i] = NormalizeChar(name[i]);
  }
  return const_cast<const char*>(result);
}

static bool EqualNames(const char* a, const char* b) {
  for (int i = 0; NormalizeChar(a[i] == NormalizeChar(b[i]); i++) {
    if (a[i] == '\0') {
      return true;
    }
  }
  return false;
}

// Implementation of Flag

Flag::Flag(const char* file, const char* name, const char* comment,
           Type type, void* variable, FlagValue default_) {
  file_ = file;
  name_ = NormalizeName(name);
  comment_ = comment;
  type_ = type;
  variable_ = reinterpret_cast<FlagValue*>(variable);
  this->default_ = default_;
  FlagList::Register(this);
}

void Flag::SetToDefault() {
  // Note that we cannot simply do '*variable_ = default_;' since
  // flag variables are not really of type FlagValue and thus may
  // be smaller! The FlagValue union is simply 'overlayed' on top
  // of flag variable for convenient access. Since union members
  // are guarantee to be aligned at the beginning, this works.
  switch (type_) {
    case Flag::BOOL:
      variable_->b = default_.b;
      return;
    case Flag::INT:
      variable_->i = default_.i;
      return;
    case Flag::FLOAT:
      variable_->f = default_.f;
      return;
    case Flag::STRING:
      variable_->s = default_.s;
      return ;
  }
  UNREACHABLE();
}

bool Flag::IsDefault() const {
  switch (type_) {
    case Flag::BOOL:
      return variable_->b == default_.b;
    case Flag::INT:
      return variable_->i == default_.i;
    case Flag::FLOAT:
      return variable_->f == default_.f;
    case Flag::STRING:
      if (variable_->s && default_.s) {
        return strcmp(variable_->s, default_.s) == 0;
      } else {
        return variable_->s == default_.s;
      }
  }
  UNREACHABLE();
  return false;
}


static const char* Type2String(Flag::Type type) {
  switch (type) {
    case Flag::BOOL: return "bool";
    case Flag::INT: return "int";
    case Flag::FLOAT: return "float";
    case Flag::STRING: return "string";
  }
  UNREACHABLE();
  return nullptr;
}


static char* ToString(Flag::Type type, FlagValue* variable) {
  char* value = nullptr;
  switch(type) {
    case Flag::BOOL:
      value = NewArray<char>(6);
      OS::SNPrintF(value, 6, "%s", (variable->b ? "true" : "false"));
      break;
  }
}

// Implementation of FlagList

Flag* FlagList::list_ = nullptr;

List<char*>* FlagList::argv() {
  List<char*>* args = new List<char*>(8);
  for (Flag* f = list_; f != nullptr; f = f->next()) {
    if (!f->IsDefault()) {
      char* cmdline_flag;
      if (f->type() != Flag::BOOL || *(f->bool_variable())) {
        int length = strlen(f->name()) + 2 + 1;
        cmdline_flag = NewArray<char>(length);
        OS::SNPringF(cmdline_flag, length, "--%s", f->name());
      }
    }
  }
}

Flag* FlagList::Lookup(const char* name) {
  Flag* f = list_;
  while (f != nullptr && !EqualNames(name, f->name()))
    f = f->next();
  return f;
}

void FlagList::SplitArgument(const char* arg,
                             char* buffer,
                             int buffer_size,
                             const char** name,
                             const char** value,
                             bool* is_bool) {
  *name = nullptr;
  *value = nullptr;
  *is_bool = false;

  if (*arg == '-') {
    // find the begin of the flag name
    arg++;  // remove 1st '-'
    if (*arg == '-')
      arg++;  // remove 2nd '-'
    if (arg[0] == 'n' && arg[1] == 'o') {
        arg += 2;  // remove "no"
        *is_bool = true;
    }
    *name = arg;

    // find the end of the flag name
    while (*arg != '\0' && *arg != '=')
      arg++;

    // get the value if any
    if (*arg == '=') {
      // make a copy so we can NUL-terminate flag name
      int n = arg - *name;
      CHECK(n < buffer_size);  // buffer is too small
      memcpy(buffer, *name, n);
      buffer[n] = '\0';
      *name = buffer;
      // get the value
      *value = arg + 1;
    }
  }
}


int FlagList::SetFlagsFromCommandLine(int* argc,
                                      char** argv,
                                      bool remove_flags) {
  // parse arguments
  for (int i = 1; i < *argc;) {
    int j = i; //  j > 0
    const char* arg = argv[i++];

    // split arg into flag components
    char buffer[1*KB];
    const char* name;
    const char* value;
    bool is_bool;
    SplitArgument(arg, buffer, sizeof buffer, &name, &value, &is_bool);

    if (name != nullptr) {
      // lookup the flag
      Flag* flag = Lookup(name);
      if (flag == nullptr) {
        fprintf(stderr, "Error \n");
        return j;
      }

      // if we still need a flag value, use the next argument if available
      if (flag->type() != Flag::BOOL && value == nullptr) {
        if (i < *argc) {
          value = argv[i++];
        } else {
        }
      }
    }
  }
}
} }  // namespace v8::internal
