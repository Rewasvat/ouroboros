
#include <cstdio>
#include <opa/utils/idgenerator.h>

namespace opa {
namespace utils {

using std::unordered_set;

IDGenerator::IDGenerator(int min_id, int max_id, int error_value) :
    current_id_(min_id),
      min_id_(min_id),
      max_id_(max_id),
      error_value_(error_value)  {
#ifdef DEBUG
    if ( min_id > max_id ) {
      printf("Ouroboros - IdGenerator\n");
      printf("The min_id is greater than the max_id"); 
      printf("(%d > %d)\n", min_id, max_id);
    }
#endif
}


int IDGenerator::GenerateID() {
    if (!unused_ids_.empty()) {
        int ret = (*unused_ids_.begin());
        unused_ids_.erase(ret);
        return ret;
    }
    if (current_id_ > max_id_) return error_value_;
    return current_id_++;
}

int IDGenerator::ReleaseID(int id) {
    if (id < min_id_ || id >= current_id_) return error_value_;
    if (unused_ids_.size() == range()) return error_value_;
    if (unused_ids_.insert(id).second == false) return error_value_;
    return id;
}

} // namespace utils
} // namespace opa
