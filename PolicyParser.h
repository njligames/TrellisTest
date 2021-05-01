#include <vector>
#include <string>
#include <set>
#include <map>

#include "PolicyData.h"

using namespace std;

class Policy;

enum RuleType{Colonel, Ranchers, MAX_RULES};

class RuleIssues {
public:
    virtual ~RuleIssues(){}
};

class ColonelRuleIssues : public RuleIssues {
    
public:
    bool mNameValid;
    bool mAddressValid;
    bool mEmailValid;
    bool mPrimaryDriversLicenseNumberValid;
    bool mPrimaryBirthdayRangeStartValid;
    bool mPrimaryGenderValid;
    

    ColonelRuleIssues():
    mNameValid(false),
    mAddressValid(false),
    mEmailValid(false),
    mPrimaryDriversLicenseNumberValid(false),
    mPrimaryBirthdayRangeStartValid(false),
    mPrimaryGenderValid(false){}
    
    virtual ~ColonelRuleIssues(){}
};

class RanchersRuleIssues : public RuleIssues {
public:
    bool mNameValid;
    bool mAddressValid;
    bool mEmailValid;
    bool mPrimaryDriversLicenseNumberValid;
    bool mPrimaryBirthdayRangeStartValid;
    bool mPrimaryGenderValid;
    bool mPhoneNumberValid;
    bool mAllDriversLicenseNumberValid;
    

    RanchersRuleIssues():
    mNameValid(false),
    mAddressValid(false),
    mEmailValid(false),
    mPrimaryBirthdayRangeStartValid(false),
    mPhoneNumberValid(false),
    mAllDriversLicenseNumberValid(false)
    {}
    
    virtual ~RanchersRuleIssues(){}
};

class Rules {
public:
    virtual ~Rules(){}
    virtual void printRuleIssues(const Policy &policy)const = 0;
    virtual bool hasRuleIssues(const Policy &policy, RuleIssues *issues)const = 0;
    
};

class ColonelRules : public Rules {
public:
    virtual void printRuleIssues(const Policy &policy)const override;
    virtual bool hasRuleIssues(const Policy &policy, RuleIssues *issues)const;
};

class RanchersRules : public Rules {
public:
    virtual void printRuleIssues(const Policy &policy)const override;
    virtual bool hasRuleIssues(const Policy &policy, RuleIssues *issues)const override;
};

class Policy {
public:
    Policy();
    ~Policy();
    
    void setPolicyId(const string &policyId){m_policyId=policyId;}
    void setAddress(trellis::address &_address){m_address=&_address;}
    void setName(trellis::name &_name){m_name=&_name;}
    void setEmail(shared_ptr<string> _email){m_email = _email;}
    void setPrimaryDriversLicenseNumber(shared_ptr<string> _driversLicenseNumber) {m_driversLicenseNumber=_driversLicenseNumber;}
    void setPrimaryBirthdayRangeStart(shared_ptr<string> _birthdayRangeStart){m_birthdayRangeStart=_birthdayRangeStart;}
    void setPrimaryBirthdayRangeEnd(shared_ptr<string> _birthdayRangeEnd){m_birthdayRangeEnd=_birthdayRangeEnd;}
    void setPrimaryGender(trellis::gender &_gender){m_gender=&_gender;}
    void setPhoneNumber(std::shared_ptr<std::string> _phoneNumber){m_phoneNumber=_phoneNumber;}
    void addOperator(trellis::operatorElement &_operator){m_operators.push_back(&_operator);}

    const string &getPolicyId()const{return m_policyId;}
    bool isAddressValid()const;
    bool isNameValid()const;
    bool isEmailValid()const;
    bool isPrimaryDriversLicenseNumberValid()const;
    bool isPrimaryBirthdayRangeStartValid()const;
    bool isPrimaryBirthdayRangeEndValid()const;
    bool isPrimaryGenderValid()const;
    bool isPhoneNumberValid()const;
    bool isAllDriversLicenseNumberValid()const;
protected:
    bool isDriversLicenseNumberValid(shared_ptr<string> driversLicenseNumber)const;
private:
    string m_policyId;
    trellis::address *m_address;
    trellis::name *m_name;
    shared_ptr<string> m_email;
    shared_ptr<string> m_driversLicenseNumber;
    shared_ptr<string> m_birthdayRangeStart;
    shared_ptr<string> m_birthdayRangeEnd;
    trellis::gender *m_gender;
    std::shared_ptr<std::string> m_phoneNumber;
    vector<trellis::operatorElement*> m_operators;
};

class PolicyParser {
public:
    
    static PolicyParser *const get();
    static bool destroy();

    bool parse(const string &jsonString, vector<Policy> &policies);
    void printRuleErrors(vector<Policy> &policies, RuleType ruleType);

private:
    PolicyParser();
    ~PolicyParser();

    static PolicyParser *sPolicyParser;
    
    vector<Rules*> mRules;
};

