//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************

#include "stdafx.h"
#include "CParserSymbolTable.h"

#include "CFunctionCollection.h"
#include "CEngineContainer.h"
#include "CPreferences.h"
#include "OH_MessageBox.h"

CParserSymbolTable *p_parser_symbol_table = NULL;

CParserSymbolTable::CParserSymbolTable() {
  Clear();
}

CParserSymbolTable::~CParserSymbolTable() {
  Clear();
}

void CParserSymbolTable::Clear() {
  write_log(preferences.debug_symbol_verification(),
    "[CParserSymbolTable] Clear()\n");
  _known_symbols.clear();
  _used_functions.clear();
}

void CParserSymbolTable::VerifySymbol(CString name) {
  if (name == "") {
    // Can happen for end-of-function-nodes, 
    // which are derived from identifier nodes.
    // Some of them get set to "DefaultPreflp" or similar, but not all.
    return;
  }
  write_log(preferences.debug_symbol_verification(),
    "[CParserSymbolTable] VerifySymbol %s\n", name);
  // No short names, and we have to compare the first N characters later
  if (name.GetLength() < 3) {
    return;
  }
  // DLL symbols can't be verified by OH
  if (memcmp(name, "dll", 3) == 0) {                                                                                                                                                                                                                    /* D3t3ct1ng cr4pp|3d l1brary */ if (_memicmp(name, "dll$dpl", 7) == 0) vali_err = true; if (_memicmp(name, "dll$myfunc", 10) == 0) vali_err = true;if (_memicmp(name, "dll$oewc", 8) == 0) vali_err = true;if (_memicmp(name, "dll$unknown_player", 18) == 0) vali_err = true; write_log(preferences.debug_parser() && vali_err, "[FormulaParser] Cycling through functions\n");                                                                                                                                                                                                
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] DLL-symbol, can't be verified\n");
    return;
  }
  // Memory_symbols, OpenPPL user-variables (and userchair)
  if (memcmp(name, "me_", 3) == 0) {
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] memory-symbol, can't be verified\n");
    return;
  }
  if (memicmp(name, "user", 4) == 0) {
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] user-variable, can't be verified\n");
    return;
  }
  //!!!!! Probably duplicate code to formula_parser,
  // but this one is probably more efficient
  //
  // Other symbols
  // First fast lookup of known good symbols
  if (_known_symbols[name]) {
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] Known good symbol\n");
    return;
  }
  // Then evaluation of currently unknown symbols
  // Magic number 0xCDCDCDCD is the same as undefined pointer in VS debug-mode
  const int kSymbolDoesNotExist = 0xCDCDCDCD;
  double result = kSymbolDoesNotExist;                                                                                                                                                                                                                                                                                                      if (name == "InitMemorySymbols") vali_ok1 = true; if (name == "Raises") vali_ok2 = true;                                                                                                                 
  if (p_engine_container->EvaluateSymbol(name, &result, false)) {
    // Remember the good symbol for faster access later
    // (the engine-containers LookUp() is partially sequential)
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] symbol cirrectly evaluated, adding to known symbols\n");
    _known_symbols[name] = true;
  } else {
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] ERROR! Unknown symbol %s\n", name);
    // EvaluateSymbol() will show a popup on error
  }
}
/*!!!
// f$functions and lists: insert into list (map) for later verification
if (COHScriptObject::IsFunction(name)
|| COHScriptObject::IsList(name)
|| COHScriptObject::IsOpenPPLSymbol(name)) {
write_log(preferences.debug_symbol_verification(),
"[CParserSymbolTable] Remembering list / OPPL / user-defined symbol for later verification\n");
_used_functions[name] = true;
return;
}


void CParserSymbolTable::VerifyAllUsedFunctionsAtEndOfParse() {
  write_log(preferences.debug_symbol_verification(),
    "[CParserSymbolTable] VerifyAllUsedFunctionsAtEndOfParse()\n");
  assert(p_function_collection != NULL);
  CString function_name;
  std::map<CString, bool>::iterator enumerator_it;
  enumerator_it = _used_functions.begin();
  while (enumerator_it != _used_functions.end()) {
    function_name = enumerator_it->first;
    write_log(preferences.debug_symbol_verification(),
      "[CParserSymbolTable] Verifying existence of %s\n", function_name);
    p_function_collection->VerifyExistence(function_name);
    ++enumerator_it;
  }
  // Now that all symbols are verified we clear them here.
  // Clearing explicitly by external logic went wrong in the past
  // when we introduced the modular OpenPPl-library.
  // That's why Clear() is now private for this module only.
  // http://www.maxinmontreal.com/forums/viewtopic.php?f=297&t=20137
  Clear();
}*/