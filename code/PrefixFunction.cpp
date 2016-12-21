std::vector<int> prefix_function(const std::string& str) {
  std::vector<int> prefs(str.size(), 0);
  for (int i = 1; i < str.size(); ++i) {
    int pref = prefs[i - 1];
    while (pref > 0 && str[i] != str[pref]) {
      pref = prefs[pref - 1];
    }
    if (str[i] == str[pref]) {
      ++pref;
    }
    prefs[i] = pref;
  }
  return prefs;
}

std::vector<int> z_function(const std::string& str) {
  std::vector<int> zfunc(str.size(), 0);
  zfunc[0] = str.size();
  for (int i = 1, left = 0, right = 0; i < str.size(); ++i) {
    if (i <= right) {
      zfunc[i] = std::min(right - i + 1, zfunc[i - left]);
    }
    while (i + zfunc[i] < str.size() && str[zfunc[i]] == str[i + zfunc[i]]) {
      ++zfunc[i];
    }
    if (i + zfunc[i] - 1 > right) {
      left = i;
      right = i + zfunc[i] - 1;
    }
  }
  return zfunc;
}

std::string from_prefix_function(const std::vector<int>& prefs) {
  std::string str(prefs.size(), '.');
  char current_symbol = 'a';
  for (int i = 0; i < prefs.size(); ++i) {
    if (prefs[i] > 0) {
      str[i] = str[prefs[i] - 1];
    }
    else {
      str[i] = current_symbol++;
    }
  }
  return str;
}

std::vector<int> prefix_to_z(const std::vector<int>& prefs) {
  return z_function(from_prefix_function(prefs));
}

std::vector<int> z_to_prefix(const std::vector<int>& z_func) {
  std::vector<int> prefs(z_func.size(), 0);
  for (int i = 1; i < z_func.size(); ++i) {
    prefs[i + z_func[i] - 1] = std::max(prefs[i + z_func[i] - 1], z_func[i]);
  }
  for (int i = z_func.size() - 2; i >= 0; --i) {
    prefs[i] = std::max(prefs[i + 1] - 1, prefs[i]);
  }
  return prefs;
}