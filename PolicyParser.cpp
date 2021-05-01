#include "PolicyParser.h"
#include "PolicyData.h"
#include <iostream>

void ColonelRules::printRuleIssues(const Policy &policy)const {
    vector<string> *missingVector = new vector<string>;
    
    if(!policy.isNameValid())missingVector->push_back("name");
    if(!policy.isAddressValid())missingVector->push_back("address");
    if(!policy.isEmailValid())missingVector->push_back("email");
    if(!policy.isPrimaryDriversLicenseNumberValid())missingVector->push_back("license");
    if(!policy.isPrimaryBirthdayRangeStartValid())missingVector->push_back("birthday");
    if(!policy.isPrimaryGenderValid())missingVector->push_back("gender");
    
    if(missingVector->size() > 0) {
        string result =  string("Missing items for policyId ");
        result += policy.getPolicyId();
        result += " ";
        for(vector<string>::iterator iter = missingVector->begin(); iter != missingVector->end(); iter++) {
            result += *iter;
            result += " ";
        }
        cout << result << endl;
    }
    delete missingVector;
}

bool ColonelRules::hasRuleIssues(const Policy &policy, RuleIssues *issues)const {
    ColonelRuleIssues *_issues = (ColonelRuleIssues*)issues;
    bool valid(true);
    
    _issues->mNameValid = policy.isNameValid();
    valid = valid && policy.isNameValid();
    
    _issues->mAddressValid = policy.isAddressValid();
    valid = valid && policy.isAddressValid();
    
    _issues->mEmailValid = policy.isEmailValid();
    valid = valid && policy.isEmailValid();
    
    _issues->mPrimaryDriversLicenseNumberValid = policy.isPrimaryDriversLicenseNumberValid();
    valid = valid && policy.isPrimaryDriversLicenseNumberValid();
    
    _issues->mPrimaryBirthdayRangeStartValid = policy.isPrimaryBirthdayRangeStartValid();
    valid = valid && policy.isPrimaryBirthdayRangeStartValid();
    
    _issues->mPrimaryGenderValid = policy.isPrimaryGenderValid();
    valid = valid && policy.isPrimaryGenderValid();
    
    return valid;
}

void RanchersRules::printRuleIssues(const Policy &policy)const {
    vector<string> *missingVector = new vector<string>;
    
    if(!policy.isNameValid())missingVector->push_back("name");
    if(!policy.isAddressValid())missingVector->push_back("address");
    if(!policy.isEmailValid())missingVector->push_back("email");
    if(!policy.isPrimaryBirthdayRangeStartValid())missingVector->push_back("birthday");
    if(!policy.isPhoneNumberValid())missingVector->push_back("phonenumber");
    if(!policy.isAllDriversLicenseNumberValid())missingVector->push_back("license");
    
    if(missingVector->size() > 0) {
        string result =  string("Missing items for policyId ");
        result += policy.getPolicyId();
        result += " ";
        for(vector<string>::iterator iter = missingVector->begin(); iter != missingVector->end(); iter++) {
            result += *iter;
            result += " ";
        }
        cout << result << endl;
    }
    delete missingVector;
}

bool RanchersRules::hasRuleIssues(const Policy &policy, RuleIssues *issues)const {
    RanchersRuleIssues *_issues = (RanchersRuleIssues*)issues;
    bool valid(true);
    
    _issues->mNameValid = policy.isNameValid();
    valid = valid && policy.isNameValid();
    
    _issues->mAddressValid = policy.isAddressValid();
    valid = valid && policy.isAddressValid();
    
    _issues->mEmailValid = policy.isEmailValid();
    valid = valid && policy.isEmailValid();
    
//    _issues->mPrimaryDriversLicenseNumberValid = policy.isPrimaryDriversLicenseNumberValid();
//    valid = valid && policy.isPrimaryDriversLicenseNumberValid();
    
    _issues->mPrimaryBirthdayRangeStartValid = policy.isPrimaryBirthdayRangeStartValid();
    valid = valid && policy.isPrimaryBirthdayRangeStartValid();
    
//    _issues->mPrimaryGenderValid = policy.isPrimaryGenderValid();
//    valid = valid && policy.isPrimaryGenderValid();
    
    _issues->mPhoneNumberValid = policy.isPhoneNumberValid();
    valid = valid && policy.isPhoneNumberValid();
    
    _issues->mAllDriversLicenseNumberValid = policy.isAllDriversLicenseNumberValid();
    valid = valid && policy.isAllDriversLicenseNumberValid();
    
    return valid;
}


Policy::Policy() :
m_policyId(""),
m_address(nullptr),
m_name(nullptr),
m_email(nullptr),
m_driversLicenseNumber(nullptr),
m_birthdayRangeStart(nullptr),
m_birthdayRangeEnd(nullptr),
m_gender(nullptr),
m_phoneNumber(nullptr) {

}

Policy::~Policy() {

}

bool Policy::isAddressValid()const {
    function<bool(trellis::address *)> isActualAddress = [](trellis::address *address) {
        // TODO: validate if this is an actual address
        return true;
    };
    
    if(nullptr == m_address) return false;
    if((nullptr == m_address->number) || m_address->number->empty()) return false;
    if((nullptr == m_address->street) || m_address->street->empty()) return false;
    if(m_address->city.empty()) return false;
    if(m_address->state.empty()) return false;
    if(m_address->zip.empty()) return false;
    
    return isActualAddress(m_address);
}

bool Policy::isNameValid()const {
    if(nullptr == m_name) return false;
    return true;

}
bool Policy::isEmailValid()const {
    function<bool(shared_ptr<string>)> isActualEmailAddress = [](shared_ptr<string>) {
        // TODO: validate if this is an actual email address
        return true;
    };
    
    if(nullptr == m_email) return false;
    return isActualEmailAddress(m_email);
}

bool Policy::isPrimaryDriversLicenseNumberValid()const {
    return isDriversLicenseNumberValid(m_driversLicenseNumber);
}

bool Policy::isPrimaryBirthdayRangeStartValid()const {
    function<bool(shared_ptr<string>)> isValidBirthday = [](shared_ptr<string>) {
        // TODO: validate if this is an actual birthday
        return true;
    };
    
    if(nullptr == m_birthdayRangeStart) return false;
    return isValidBirthday(m_birthdayRangeStart);
}

bool Policy::isPrimaryBirthdayRangeEndValid()const {
    function<bool(shared_ptr<string>)> isValidBirthday = [](shared_ptr<string>) {
        // TODO: validate if this is an actual birthday
        return true;
    };
    
    if(nullptr == m_birthdayRangeEnd) return false;
    return isValidBirthday(m_birthdayRangeEnd);
}

bool Policy::isPrimaryGenderValid()const {
    if(nullptr == m_gender) return false;
    return true;
}
        
bool Policy::isPhoneNumberValid()const {
    function<bool(shared_ptr<string>)> isValidPhoneNumber = [](shared_ptr<string>) {
        // TODO: validate if this is an actual phone number
        return true;
    };
    
    if(nullptr == m_phoneNumber) return false;
    return isValidPhoneNumber(m_phoneNumber);
}

bool Policy::isAllDriversLicenseNumberValid()const {
    bool ret = true;
    for(int i = 0; i < m_operators.size(); i++) {
        ret = ret && isDriversLicenseNumberValid(m_operators[i]->driversLicenseNumber);
    }
    return ret;
}

bool Policy::isDriversLicenseNumberValid(shared_ptr<string> driversLicenseNumber)const{
    function<bool(shared_ptr<string>)> isActualDriversLicenseNumber = [](shared_ptr<string>) {
        // TODO: validate if this is an actual drivers license number
        return true;
    };
    
    if(nullptr == driversLicenseNumber) return false;
    return isActualDriversLicenseNumber(driversLicenseNumber);
}

PolicyParser *PolicyParser::sPolicyParser = nullptr;

PolicyParser *const PolicyParser::get() {
    if(nullptr == sPolicyParser) {
        sPolicyParser = new PolicyParser();
    }
    return sPolicyParser;
}

bool PolicyParser::destroy() {
    if(nullptr != sPolicyParser) {
        delete sPolicyParser;
    }
    sPolicyParser = nullptr;
}

bool PolicyParser::parse(const string &jsonString, vector<Policy> &policies) {
    string empty("");
    bool is = empty.empty();
    
    static trellis::welcome data = nlohmann::json::parse(jsonString);
    for(int i = 0; i < data.size(); i++) {
        trellis::welcomeElement &_welcomeElement = data[i];
        
        Policy policy;
        
        policy.setPolicyId(_welcomeElement.policyId);
        policy.setAddress(_welcomeElement.policyHolder.address);
        policy.setName(_welcomeElement.policyHolder.name);
        policy.setEmail(_welcomeElement.policyHolder.email);
        policy.setPhoneNumber(_welcomeElement.policyHolder.phoneNumber);
        
        for(int j = 0; j < _welcomeElement.operators.size(); j++) {
            trellis::operatorElement &_operatorElement = _welcomeElement.operators[j];
            
            policy.addOperator(_operatorElement);
            
            if(_operatorElement.isPrimary) {
                policy.setPrimaryDriversLicenseNumber(_operatorElement.driversLicenseNumber);
                policy.setPrimaryBirthdayRangeStart(_operatorElement.birthdayRange.start);
                policy.setPrimaryBirthdayRangeEnd(_operatorElement.birthdayRange.end);
                policy.setPrimaryGender(_operatorElement.gender);
            }
        }
        policies.push_back(policy);
    }
}

void PolicyParser::printRuleErrors(vector<Policy> &policies, RuleType ruleType) {
    for(int i = 0; i < policies.size(); i++)
        mRules[ruleType]->printRuleIssues(policies[i]);
}

PolicyParser::PolicyParser() {
    mRules.resize(MAX_RULES);
    
    Rules *rule = nullptr;
    
    rule = new RanchersRules();
    mRules[Ranchers] = rule;
    
    rule = new ColonelRules();
    mRules[Colonel] = rule;
}

PolicyParser::~PolicyParser() {
    for(int i = 0; i < mRules.size(); i++) {
        delete mRules[i];
    }
}

