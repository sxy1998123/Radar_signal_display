import axios from 'axios'
export default {
    generateSignal: (data) => {
        return axios.post('/api/signal/generate', data)
    },
    handleSignal: (data) => {
        return axios.post('/api/signal/handle', data)
    },
    getTimeDomainData: (num_unit) => {
        return axios.get(`/api/signal/time_domain_data?num_unit=${num_unit}`)
    },
    getFrequencyDomainData: (num_unit) => {
        return axios.get(`/api/signal/freq_domain_data?num_unit=${num_unit}`)
    },
    getAscanData: () => {
        return axios.get('/api/signal/ascan')
    },
    getBscanData: () => {
        return axios.get('/api/signal/bscan')
    }
}